/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 06:02:05 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/03 17:55:18 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** start parsing
*/

int				start_parsing(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("error arguments!\n");
		return (0);
	}
	if (!argument_processing(argc, argv))
		return (exit_program("error arguments!\n"));
	if (!start_thread())
		return (exit_program("thread create error!\n"));
	return (1);
}

/*
** argument parsing
*/

int				argument_processing(int argc, char **argv)
{
	if (!(g_info = (t_info *)malloc(sizeof(t_info))))
		return (0);
	if ((g_info->number = ft_atoi(argv[1])) == -1)
		return (0);
	if ((g_info->die = ft_atoi(argv[2])) == -1)
		return (0);
	if ((g_info->eat = ft_atoi(argv[3])) == -1)
		return (0);
	if ((g_info->sleep = ft_atoi(argv[4])) == -1)
		return (0);
	g_info->must_eat = -1;
	if (argc == 6 && (g_info->must_eat = ft_atoi(argv[5])) == -1)
		return (0);
	if (!(g_info->chopstic = (bool *)malloc(sizeof(bool) * g_info->number)))
		return (0);
	init_chopstics();
	if (!set_g_info())
		return (0);
	return (1);
}

/*
** g_info 처음 세팅
*/

int				set_g_info(void)
{
	int			i;

	i = 0;
	if (!(g_info->thread = (pthread_t *)malloc(
				sizeof(pthread_t) * g_info->number)))
		return (0);
	if (!(g_info->mutex = (pthread_mutex_t *)malloc(
				sizeof(pthread_mutex_t) * (g_info->number + 1))))
		return (0);
	if (!(g_info->members = (t_thread *)malloc(
				sizeof(t_thread) * g_info->number)))
		return (0);
	while (i < g_info->number + 1)
		if (pthread_mutex_init(&g_info->mutex[i++], NULL))
			return (0);
	return (1);
}

void			init_chopstics(void)
{
	int			i;

	i = 0;
	while (i < g_info->number)
		g_info->chopstic[i++] = true;
}

int				ft_atoi(const char *str)
{
	int			num;
	int			minus;

	num = 0;
	minus = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (-1);
	while (*str && (*str >= '0' && *str <= '9'))
	{
		num = num * 10 + *str - '0';
		str++;
	}
	if (*str && (*str < '0' || *str > '9'))
		return (-1);
	return (num * minus);
}
