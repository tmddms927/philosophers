/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 20:07:31 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/03 11:55:03 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** change action1
*/

void				*change_action1(t_thread *mem, int action)
{
	struct timeval	temp;
	int				i;

	i = g_info->number;
	if (action == DIE)
	{
		while (i < g_info->number * 2)
			pthread_mutex_lock(&g_info->mutex[i++]);
		printf("%ldms %d is died\n", ((mem->time.tv_sec - g_info->start.tv_sec) * 1000000 + mem->time.tv_usec - g_info->start.tv_usec) / 1000, mem->num);
		mem->action = DIE;
	}
	if (action == EAT)
	{
		gettimeofday(&temp, NULL);
		mem->time = temp;
		pthread_mutex_lock(&g_info->mutex[g_info->number + mem->num - 1]);
		printf("%ldms %d is eating\n", ((mem->time.tv_sec - g_info->start.tv_sec) * 1000000 + mem->time.tv_usec - g_info->start.tv_usec) / 1000, mem->num);
		pthread_mutex_unlock(&g_info->mutex[g_info->number + mem->num - 1]);
		mem->action = EATTING;
		ft_eat(mem);
	}
	change_action2(mem, action);
	return (0);
}

/*
** change action2
*/

void				*change_action2(t_thread *mem, int action)
{
	if (action == SLEEP)
	{
		mem->action = SLEEPING;
		printf("%ldms %d is sleeping\n", ((mem->time.tv_sec - g_info->start.tv_sec) * 1000000 + mem->time.tv_usec  - g_info->start.tv_usec) / 1000 + g_info->eat, mem->num);
		ft_sleep(mem);
	}
	if (action == THINK)
	{
		mem->action = THINK;
		printf("%ldms %d is thinking\n", ((mem->time.tv_sec - g_info->start.tv_sec) * 1000000 + mem->time.tv_usec  - g_info->start.tv_usec) / 1000 + g_info->eat + g_info->sleep, mem->num);
	}
	return (0);
}

/*
** 1 ~ N-1 philosopher's how to get chopstic
*/

void				get_chopstic1(t_thread *mem)
{
	if (*mem->l_chop)
	{
		pthread_mutex_lock(mem->l_mu);
		*mem->l_chop = false;
		mem->my_l = true;
		pthread_mutex_unlock(mem->l_mu);
	}
	if (mem->my_l && *mem->r_chop)
	{
		pthread_mutex_lock(mem->r_mu);
		*mem->r_chop = false;
		mem->my_r = true;
		pthread_mutex_unlock(mem->r_mu);
	}
	if (mem->my_l && mem->my_r && mem->action == THINK)
		change_action1(mem, EAT);
}

/*
** 1 ~ N-1 philosopher's how to get chopstic
*/

void				get_chopstic2(t_thread *mem)
{
	if (*mem->r_chop)
	{
		pthread_mutex_lock(mem->r_mu);
		mem->my_r = true;
		*mem->r_chop = false;
		pthread_mutex_unlock(mem->r_mu);
	}
	if (mem->my_r && *mem->l_chop)
	{
		pthread_mutex_lock(mem->l_mu);
		mem->my_l = true;
		*mem->l_chop = false;
		pthread_mutex_unlock(mem->l_mu);
	}
	if (mem->my_l && mem->my_r)
		change_action1(mem, EAT);
}
