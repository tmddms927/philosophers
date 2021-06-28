/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 23:23:20 by seungoh           #+#    #+#             */
/*   Updated: 2021/06/28 06:45:26 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main(int argc, char **argv)
{
	t_info *info;
	
	if (argc != 5 && argc != 6)
		printf("error arguments!\n");
	if (!(info = argument_processing(argc, argv)))
		exit_program(info, "argument error!\n");
	if (!start_thread(info))
		exit_program(info, "thread create error!\n");
	return (0);
}
