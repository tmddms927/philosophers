/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 20:07:31 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/02 06:02:30 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** change action1
*/

void				*change_action1(t_thread *mem, int action)
{
	struct timeval	temp;

	if (action == DIE)
	{
		printf("%ldms %d is died\n", mem->time / 1000, mem->num);
		mem->action = DIE;
	}
	if (action == EAT)
	{
		gettimeofday(&temp, NULL);
		mem->time = temp.tv_usec;
		printf("%ldms %d is eating\n", mem->time / 1000, mem->num);
		mem->my_eat++;
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
		printf("%ldms %d is sleeping\n", mem->time / 1000, mem->num);
		ft_sleep(mem);
	}
	if (action == THINK)
	{
		mem->action = THINK;
		printf("%ldms %d is thinking\n", mem->time / 1000, mem->num);
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
