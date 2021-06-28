/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 05:56:01 by seungoh           #+#    #+#             */
/*   Updated: 2021/06/28 06:33:34 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct		s_info
{
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
}					t_info;

/*
** parsing.c
*/

t_info				*argument_processing(int argc, char **argv);
int					ft_atoi(const char *str);

/*
** utils.c
*/

int					exit_program(t_info *info);

#endif