/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 23:26:45 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/03 16:36:21 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int					exit_program(char *s)
{
	printf("%s", s);
	if (g_info)
	{
		if (g_info->chopstic)
			free(g_info->chopstic);
		if (g_info->thread)
			free(g_info->thread);
		if (g_info->members)
			free(g_info->members);
		if (g_info->mutex)
			free(g_info->mutex);
		free(g_info);
	}
	return (0);
}

int					just_info_free(void)
{
	free(g_info);
	return (0);
}

int					ft_usleep(t_thread *mem, int time)
{
	struct timeval	temp;

	while (!gettimeofday(&temp, NULL))
	{
		if (temp.tv_sec * 1000 + temp.tv_usec / 1000 >
			mem->time.tv_sec * 1000 + mem->time.tv_usec / 1000 + time)
			return (1);
		usleep(100);
	}
	return (1);
}
