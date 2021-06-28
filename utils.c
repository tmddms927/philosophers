/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 23:26:45 by seungoh           #+#    #+#             */
/*   Updated: 2021/06/28 06:47:03 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			exit_program(t_info *info, char *s)
{
	pritnf("%s", s);
	while (*info->mutex)
	{
		free(info->mutex);
		info->mutex;
	}
	free(info);
	return (0);
}
