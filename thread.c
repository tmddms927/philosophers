/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 06:29:02 by seungoh           #+#    #+#             */
/*   Updated: 2021/06/30 05:35:15 by seungoh          ###   ########.fr       */
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
		g_info->members[i].num = i + 1;
		g_info->members[i].my_eat = 0;
		g_info->members[i].action = NOT;
		g_info->members[i].my_l = false;
		g_info->members[i].my_r = true;
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

void				*philo_action1(void *member)
{
	t_thread 		*mem;
	struct timeval	temp;

	mem = member;
	gettimeofday(&temp, NULL);
	printf("%ld %d has taken a fork\n", temp.tv_usec / 1000, mem->num);
	mem->not = temp.tv_usec;
	while (mem->action != DIE)
	{
		gettimeofday(&temp, NULL);
		if (mem->action == NOT && (temp.tv_usec - mem->not) / 1000 > g_info->die)
			return (change_action(mem, DIE));
		get_chopstic(mem);
		if (mem->action == EAT)
		{
			usleep(g_info->eat * 1000);
			change_action(mem, SLEEP);
			gettimeofday(&temp, NULL);
			mem->not = temp.tv_usec;
		}
		if (mem->action == SLEEP)
		{
			if (g_info->sleep > g_info->die)
				return (change_action(mem, DIE));
			usleep(g_info->sleep * 1000);
			change_action(mem, NOT);
			gettimeofday(&temp, NULL);
			mem->not = temp.tv_usec;
		}
	}
	return (member);
}

/*
** change action
*/
void		*change_action(t_thread *mem, int action)
{
	struct timeval	temp;

	if (action == DIE)
	{
		gettimeofday(&temp, NULL);
		printf("%ld %d is died\n", temp.tv_usec / 1000, mem->num);
		mem->action = DIE;
	}
	if (action == EAT)
	{
		gettimeofday(&temp, NULL);
		printf("%ld %d is eating\n", temp.tv_usec / 1000, mem->num);
		mem->my_l = false;
		mem->my_r = false;
		mem->my_eat++;
		pthread_mutex_lock(&g_info->mutex);
		*mem->l_chop = true;
		*mem->r_chop = true;
		pthread_mutex_unlock(&g_info->mutex);
		mem->action = EAT;
	}
	if (action == SLEEP)
	{
		mem->action = SLEEP;
		gettimeofday(&temp, NULL);
		printf("%ld %d is sleeping\n", temp.tv_usec / 1000, mem->num);
	}
	if (action == NOT)
	{
		mem->action = NOT;
		gettimeofday(&temp, NULL);
		printf("%ld %d is thinking\n", temp.tv_usec / 1000, mem->num);
	}
	return (0);
}

void		get_chopstic(t_thread *mem)
{
	if (*mem->l_chop)
	{
		mem->my_l = true;
		pthread_mutex_lock(&g_info->mutex);
		*mem->l_chop = false;
		pthread_mutex_unlock(&g_info->mutex);
	}
	if (*mem->r_chop)
	{
		mem->my_r = true;
		pthread_mutex_lock(&g_info->mutex);
		*mem->r_chop = false;
		pthread_mutex_unlock(&g_info->mutex);
	}
	if (mem->my_l && mem->my_r)
		change_action(mem, EAT);
}