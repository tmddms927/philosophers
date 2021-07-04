/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 20:07:31 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/04 00:57:20 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** change action1
*/

void				*change_action1(t_thread *mem, int action)
{
	int				i;

	i = g_info->number - 1;
	if (action == DIE)
	{
		while (++i < g_info->number * 2)
			pthread_mutex_lock(&g_info->mutex[i]);
		printf("%ldms %d is died\n", (mem->time.tv_sec - g_info->st.tv_sec) *
		1000 + (mem->time.tv_usec - g_info->st.tv_usec) / 1000, mem->num);
		mem->action = DIE;
	}
	if (action == EAT)
	{
		//pthread_mutex_lock(&g_info->mutex[g_info->number + mem->num - 1]);
		printf("%ldms %d is eating\n", (mem->time.tv_sec - g_info->st.tv_sec) *
		1000 + (mem->time.tv_usec - g_info->st.tv_usec) / 1000, mem->num);
		//pthread_mutex_unlock(&g_info->mutex[g_info->number + mem->num - 1]);
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
		printf("%ldms %d is sleeping\n", (mem->pt.tv_sec - g_info->st.tv_sec) *
		1000 + (mem->pt.tv_usec - g_info->st.tv_usec) / 1000, mem->num);
		ft_sleep(mem);
	}
	if (action == THINK)
	{
		mem->action = THINK;
		printf("%ldms %d is thinking\n", (mem->pt.tv_sec - g_info->st.tv_sec) *
		1000 + (mem->pt.tv_usec - g_info->st.tv_usec) / 1000, mem->num);
	}
	return (0);
}

/*
** 1 ~ N-1 philosopher's how to get chopstic
*/

void				get_chopstic1(t_thread *mem)
{
	struct timeval	temp;

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
	{
		gettimeofday(&temp, NULL);
		mem->time = temp;
		change_action1(mem, EAT);
		printf("%ldms %d has taken a fork\n",
		(mem->time.tv_sec - g_info->st.tv_sec) * 1000 +
		(mem->time.tv_usec - g_info->st.tv_usec) / 1000, mem->num);
	}
}

/*
** 1 ~ N-1 philosopher's how to get chopstic
*/

void				get_chopstic2(t_thread *mem)
{
	struct timeval	temp;

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
	if (mem->my_l && mem->my_r && mem->action == THINK)
	{
		gettimeofday(&temp, NULL);
		mem->time = temp;
		change_action1(mem, EAT);
		printf("%ldms %d has taken a fork\n",
		(mem->time.tv_sec - g_info->st.tv_sec) *
		1000 + (mem->time.tv_usec - g_info->st.tv_usec) / 1000, mem->num);
	}
}
