/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 06:29:02 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/02 05:32:26 by seungoh          ###   ########.fr       */
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
	g_info->members[i].action = THINK;
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
	mem->time = temp.tv_usec;
	printf("%ldms %d has taken a fork\n", mem->time / 1000, mem->num);
	while (mem->action != DIE && !gettimeofday(&temp, NULL))
	{
		if (mem->action == THINK && temp.tv_usec - mem->time > g_info->die * 1000)
		{
			mem->time = temp.tv_usec;
			return (change_action1(mem, DIE));
		}
		get_chopstic1(mem);
	}
	return (member);
}
