/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 06:29:02 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/03 11:58:49 by seungoh          ###   ########.fr       */
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
	if (i == g_info->number - 1)
	{	if (pthread_create(&g_info->thread[i], NULL, philo_action2,
			(void *)&g_info->members[i]))
			return (0);
	}
	else if (pthread_create(&g_info->thread[i], NULL, philo_action1,
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
	mem->time = temp;
	if (mem->num == 1)
		g_info->start = temp;
	printf("%ldms %d has taken a fork\n", ((mem->time.tv_sec - g_info->start.tv_sec) * 1000000 + mem->time.tv_usec - g_info->start.tv_usec) / 1000, mem->num);
	while (mem->action != DIE && !gettimeofday(&temp, NULL))
	{
		if (((temp.tv_sec - mem->time.tv_sec) * 1000000 + temp.tv_usec  - mem->time.tv_usec) > g_info->die * 1000)
		{
			mem->time = temp;
			return (change_action1(mem, DIE));
		}
		if (mem->my_eat == g_info->must_eat)
			return (member);
		if (mem->action == THINK)
			get_chopstic1(mem);
	}
	return (member);
}

/*
** thread action2
*/

void				*philo_action2(void *member)
{
	t_thread		*mem;
	struct timeval	temp;

	mem = member;
	gettimeofday(&temp, NULL);
	mem->time = temp;
	if (mem->num == 1)
		g_info->start = temp;
	printf("%ldms %d has taken a fork\n", ((mem->time.tv_sec - g_info->start.tv_sec) * 1000000 + mem->time.tv_usec - g_info->start.tv_usec) / 1000, mem->num);
	while (mem->action != DIE && !gettimeofday(&temp, NULL))
	{
		if (((temp.tv_sec - mem->time.tv_sec) * 1000000 + temp.tv_usec  - mem->time.tv_usec) > g_info->die * 1000)
		{
			mem->time = temp;
			return (change_action1(mem, DIE));
		}
		if (mem->my_eat == g_info->must_eat)
			return (member);
		if (mem->action == THINK)
			get_chopstic2(mem);
	}
	return (member);
}