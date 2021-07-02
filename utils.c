/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 23:26:45 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/02 06:34:44 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			exit_program(char *s)
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

int			just_info_free(void)
{
	free(g_info);
	return (0);
}

int		ft_usleep(t_thread *mem, int time)
{
	struct timeval	temp;

	if (mem->time / 1000 + time > 1000)
		mem->time = mem->time - 1000 * 1000;
	//printf("%d before : %ld\n", mem->num, mem->time/1000);
	while (!gettimeofday(&temp, NULL))
	{
		//printf("%d %ld, %ld\n", mem->num, temp.tv_usec / 1000, mem->time / 1000 + time);
		if ((temp.tv_usec / 1000 == mem->time / 1000 + time))
		{
			//printf("%d finished\n", mem->num);
			mem->time = temp.tv_usec;
			return (1);
		}
		usleep(300);
	}
	return (1);
}