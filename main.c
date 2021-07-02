/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 23:23:20 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/02 06:35:56 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		main(int argc, char **argv)
{
	int	i;
	int eat;
	struct timeval	temp;

	if (!start_parsing(argc, argv))
		return (0);
	while (!gettimeofday(&temp, NULL))
	{
		i = -1;
		eat = 0;
		printf("%ld\n", temp.tv_usec / 1000);
		while (++i < g_info->number)
		{
			if (g_info->members[i].action == DIE)
				return (0);
			if (g_info->must_eat == g_info->members[i].my_eat)
				eat++;
		}
		if (eat == g_info->number)
			return (0);
	}
	return (0);
}
