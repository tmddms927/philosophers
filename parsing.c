/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 06:02:05 by seungoh           #+#    #+#             */
/*   Updated: 2021/06/28 06:34:46 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** argument parsing
*/

t_info			*argument_processing(int argc, char **argv)
{
	t_info		*info;
	
	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (0);
	if ((info->number = ft_atoi(argv[1])) == -1)
		return (0);
	if ((info->die = ft_atoi(argv[2])) == -1)
		return (0);
	if ((info->eat = ft_atoi(argv[3])) == -1)
		return (0);
	if ((info->sleep = ft_atoi(argv[4])) == -1)
		return (0);
	info->must_eat = -1;
	if (argc == 6 && (info->must_eat = ft_atoi(argv[5])) == -1)
		return (0);
	if (!(info->thread = (pthread_t *)malloc(sizeof(pthread_t) * info->number)))
		return (0);
	if (!(info->mutex = (pthread_mutex_t *)malloc
			(sizeof(pthread_mutex_t) * (info->number - 1))))
		return (0);
	return (info);
}

int			ft_atoi(const char *str)
{
	int		num;
	int		minus;

	num = 0;
	minus = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		printf("argument error!\n");
		return (-1);
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		num = num * 10 + *str - '0';
		str++;
	}
	if (*str && (*str < '0' || *str > '9'))
	{
		printf("argument error!\n");
		return (-1);
	}
	return (num * minus);
}