/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 04:56:03 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/02 08:33:04 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void				ft_eat(t_thread *mem)
{
	if (ft_usleep(mem, g_info->eat))
	{
		pthread_mutex_lock(mem->l_mu);
		*mem->l_chop = true;
		mem->my_l = false;
		pthread_mutex_unlock(mem->l_mu);
		pthread_mutex_lock(mem->r_mu);
		*mem->r_chop = true;
		mem->my_r = false;
		mem->my_eat++;
		pthread_mutex_unlock(mem->r_mu);
		change_action1(mem, SLEEP);
	}
}

void				*ft_sleep(t_thread *mem)
{
	if (g_info->sleep > g_info->die)
		return (change_action1(mem, DIE));
	if (ft_usleep(mem, g_info->sleep))
		change_action1(mem, THINK);
	return (0);
}
