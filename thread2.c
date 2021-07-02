/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 20:07:31 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/01 23:09:37 by seungoh          ###   ########.fr       */
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
		gettimeofday(&temp, NULL);
		printf("%ldms %d is died\n", temp.tv_usec / 1000, mem->num);
		mem->action = DIE;
	}
	if (action == EAT)
	{
		gettimeofday(&temp, NULL);
		printf("%ldms %d is eating\n", temp.tv_usec / 1000, mem->num);
		mem->my_eat++;
		pthread_mutex_lock(mem->l_mu);
		mem->my_l = false;
		*mem->l_chop = true;
		pthread_mutex_unlock(mem->l_mu);
		pthread_mutex_lock(mem->r_mu);
		*mem->r_chop = true;
		mem->my_r = false;
		pthread_mutex_unlock(mem->r_mu);
		mem->action = EAT;
	}
	change_action2(mem, action);
	return (0);
}

/*
** change action2
*/

void				*change_action2(t_thread *mem, int action)
{
	struct timeval	temp;

	if (action == SLEEP)
	{
		mem->action = SLEEP;
		gettimeofday(&temp, NULL);
		printf("%ldms %d is sleeping\n", temp.tv_usec / 1000, mem->num);
	}
	if (action == NOT)
	{
		mem->action = NOT;
		gettimeofday(&temp, NULL);
		printf("%ldms %d is thinking\n", temp.tv_usec / 1000, mem->num);
	}
	return (0);
}

void				get_chopstic(t_thread *mem)
{
	if (*mem->l_chop)
	{
		pthread_mutex_lock(mem->l_mu);
		mem->my_l = true;
		*mem->l_chop = false;
		pthread_mutex_unlock(mem->l_mu);
	}
	if (*mem->r_chop)
	{
		pthread_mutex_lock(mem->r_mu);
		mem->my_r = true;
		*mem->r_chop = false;
		pthread_mutex_unlock(mem->r_mu);
	}
	if (mem->my_l && mem->my_r)
		change_action1(mem, EAT);
}
