/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 06:29:02 by seungoh           #+#    #+#             */
/*   Updated: 2021/06/28 06:40:20 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** create thread
*/

int			start_thread(t_info *info)
{
    int		i;

	i = 0;
	while (i++ < info->number)
	{
		if (pthread_create(&info->thread[i], NULL, philo_action, (void *)info))
			return (0);
		if (info->number - 1 == i && pthread_mutex_init(&info->mutex[i], NULL))
			return (0);
	}
}