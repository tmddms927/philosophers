/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 05:56:01 by seungoh           #+#    #+#             */
/*   Updated: 2021/07/03 11:52:03 by seungoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

# define THINK 1
# define EAT 2
# define EATTING 3
# define SLEEP 4
# define SLEEPING 5
# define DIE 6

typedef struct		s_thread
{
	int				num;

	struct timeval	time;
	int				my_eat;
	int				action;
	bool			my_l;
	bool			my_r;
	bool			*l_chop;
	bool			*r_chop;
	pthread_mutex_t	*l_mu;
	pthread_mutex_t	*r_mu;
}					t_thread;

typedef struct		s_info
{
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	bool			*chopstic;
	struct timeval	start;
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
	t_thread		*members;
}					t_info;

t_info				*g_info;

/*
** parsing.c
*/

int					start_parsing(int argc, char **argv);
int					argument_processing(int argc, char **argv);
int					set_g_info();
void				init_chopstics();
int					ft_atoi(const char *str);

/*
** utils.c
*/

int					exit_program(char *s);
int					just_info_free();
int					ft_usleep(t_thread *mem, int time);

/*
** thread.c
*/

int					start_thread();
int					thread_info_set(int i);
void				*philo_action1(void *info);
void				*philo_action2(void *member);
void				*change_action1();
void				*change_action2(t_thread *mem, int action);
void				get_chopstic1(t_thread *mem);
void				get_chopstic2(t_thread *mem);

void				ft_eat(t_thread *mem);
void				*ft_sleep(t_thread *mem);

#endif
