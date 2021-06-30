/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 05:56:01 by seungoh           #+#    #+#             */
/*   Updated: 2021/06/30 03:38:10 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>

# define NOT 1
# define EAT 2
# define SLEEP 3
# define DIE 4

typedef struct		s_thread
{
	int				my_die;
	int				my_eat;
	int				my_sleep;
	int				action;
	bool			*l_chop;
	bool			*r_chop;
}					t_thread;

typedef struct		s_info
{
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	bool			*chopstic;
	pthread_t		*thread;
	pthread_mutex_t	mutex;
	t_thread		*members;
}					t_info;

t_info				*g_info;

/*
** parsing.c
*/

int					argument_processing(int argc, char **argv);
void				init_chopstics();
int					ft_atoi(const char *str);

/*
** utils.c
*/

int					exit_program(char *s);
int					just_info_free();

/*
** thread.c
*/

int					start_thread();
void				*philo_action1(void *info);

#endif