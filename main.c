/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 23:23:20 by seungoh           #+#    #+#             */
/*   Updated: 2021/06/30 02:45:26 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main(int argc, char **argv)
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
	return (0);
}
