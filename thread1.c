/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 06:29:02 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/01 20:08:08 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** create thread
*/

int					start_thread(void)
{
	int				i;

	i = 0;
	while (i < g_info->number)
	{
		if (!thread_info_set(i))
			return (0);
		i++;
	}
	return (1);
}

/*
** thread info setting
*/

int					thread_info_set(int i)
{
	g_info->members[i].num = i + 1;
	g_info->members[i].my_eat = 0;
	g_info->members[i].action = NOT;
	g_info->members[i].my_l = false;
	g_info->members[i].my_r = false;
	g_info->members[i].l_chop = &g_info->chopstic[i];
	if (i == g_info->number - 1)
		g_info->members[i].r_chop = &g_info->chopstic[0];
	else
		g_info->members[i].r_chop = &g_info->chopstic[i + 1];
	g_info->members[i].l_mu = &g_info->mutex[i];
	if (i == g_info->number - 1)
		g_info->members[i].r_mu = &g_info->mutex[0];
	else
		g_info->members[i].r_mu = &g_info->mutex[i + 1];
	if (pthread_create(&g_info->thread[i], NULL, philo_action1,
		(void *)&g_info->members[i]))
		return (0);
	return (1);
}

/*
** thread action1
*/

void				*philo_action1(void *member)
{
	t_thread		*mem;
	struct timeval	temp;

	mem = member;
	gettimeofday(&temp, NULL);
	printf("%dms %d has taken a fork\n", temp.tv_usec / 1000, mem->num);
	mem->not = temp.tv_usec;
	while (mem->action != DIE)
	{
		gettimeofday(&temp, NULL);
		if (mem->action == NOT && temp.tv_usec - mem->not > g_info->die * 1000)
			return (change_action1(mem, DIE));
		get_chopstic(mem);
		if (mem->action == EAT)
		{
			usleep(g_info->eat * 1000);
			change_action1(mem, SLEEP);
			gettimeofday(&temp, NULL);
			mem->not = temp.tv_usec;
		}
		if (mem->action == SLEEP)
		{
			if (g_info->sleep > g_info->die)
				return (change_action1(mem, DIE));
			usleep(g_info->sleep * 1000);
			change_action1(mem, NOT);
			gettimeofday(&temp, NULL);
			mem->not = temp.tv_usec;
		}
	}
	return (member);
}
