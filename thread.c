/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 06:29:02 by seungoh           #+#    #+#             */
/*   Updated: 2021/06/30 03:39:07 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** create thread
*/

int			start_thread()
{
    int		i;

	i = 0;
	while (i < g_info->number)
	{
		g_info->members[i].my_die = 0;
		g_info->members[i].my_eat = i;
		g_info->members[i].my_sleep = 0;
		g_info->members[i].action = NOT;
		g_info->members[i].l_chop = &g_info->chopstic[i];
		if (i == g_info->number - 1)
			g_info->members[i].r_chop = &g_info->chopstic[0];
		else
			g_info->members[i].r_chop = &g_info->chopstic[i + 1];
		if (pthread_create(&g_info->thread[i], NULL, philo_action1, (void *)&g_info->members[i]))
			return (0);
		if (g_info->number - 1 == i && pthread_mutex_init(&g_info->mutex, NULL))
			return (0);
		i++;
	}
	return (1);
}

/*
** thread action1
*/

void		*philo_action1(void *member)
{
	t_thread *temp = member;
	printf("create thread : %d\n", temp->my_eat);
	while (temp->action != DIE)
	{
		if (*temp->l_chop)
		{
			pthread_mutex_lock(&g_info->mutex);
			*temp->l_chop = false;
			printf("left, %d\n", temp->my_eat);
			pthread_mutex_unlock(&g_info->mutex);
		}
		if (*temp->r_chop)
		{
			pthread_mutex_lock(&g_info->mutex);
			printf("right, %d\n", temp->my_eat);
			*temp->r_chop = false;
			pthread_mutex_unlock(&g_info->mutex);
		}
	}
	return (member);
}
