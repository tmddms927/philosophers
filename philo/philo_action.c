/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 04:56:03 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/03 16:44:15 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void				ft_eat(t_thread *mem)
{
	struct timeval	temp;

	if (ft_usleep(mem, g_info->eat))
	{
		pthread_mutex_lock(mem->l_mu);
		*mem->l_chop = true;
		mem->my_l = false;
		pthread_mutex_unlock(mem->l_mu);
		pthread_mutex_lock(mem->r_mu);
		*mem->r_chop = true;
		mem->my_r = false;
		pthread_mutex_unlock(mem->r_mu);
		mem->my_eat++;
		gettimeofday(&temp, NULL);
		mem->pt = temp;
		change_action1(mem, SLEEP);
	}
}

void				*ft_sleep(t_thread *mem)
{
	struct timeval	temp;

	if (ft_usleep(mem, g_info->sleep + g_info->eat))
	{
		gettimeofday(&temp, NULL);
		mem->pt = temp;
		change_action1(mem, THINK);
	}
	return (0);
}
