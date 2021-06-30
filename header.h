/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 05:56:01 by seungoh           #+#    #+#             */
/*   Updated: 2021/06/30 05:34:48 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

# define NOT 1
# define EAT 2
# define SLEEP 3
# define DIE 4

typedef struct		s_thread
{
	int				num;
	suseconds_t		not;
	int				my_eat;
	int				action;
	bool			my_l;
	bool			my_r;
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
void				*change_action();
void				get_chopstic(t_thread *mem);

#endif