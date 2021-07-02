/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 23:23:20 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/02 00:11:15 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		main(int argc, char **argv)
{
	int	i;
	int eat;

	if (!start_parsing(argc, argv))
		return (0);
	while (1)
	{
		i = -1;
		eat = 0;
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
