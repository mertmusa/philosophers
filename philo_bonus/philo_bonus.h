/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:24:22 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/07 10:47:19 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

struct	s_rules;
typedef struct s_philo
{
	int				philo_id;
	int				process_id;
	int				eat_counter;
	long long		last_eat;
	struct s_rules	*mrules;
}	t_philo;

typedef struct s_rules
{
	int			philo_nof;
	int			die_tto;
	int			eat_tto;
	int			sleep_tto;
	int			eat_noftep;
	long long	start_time;
	sem_t		*forks;
	sem_t		*writs;
	int			is_dead;
	int			all_eat;
	pthread_t	yep;
	pthread_t	check;
	t_philo		*philo;
}	t_rules;

//philo_ulibft
int			ft_atoi(const char *str);
int			ft_isdigit(int c);

//philo_utils
void		ft_error(char *str);
long long	get_the_time(void);
void		my_print(int philo_id, char *s, t_rules *rules);
void		time_passer(int time_tocheck, t_rules *rules);

//philo_init
int			argtoparam_init(t_rules *rules, char **argv, int argc);
int			init_continue(t_rules *rules);
int			init_continue2(t_rules *rules);

//philo_check
int			check_arg(char **argv, int argc);
int			check_arg2(char **argv, int argc);

int			start_to_thrive(t_rules *rules);
void		*routine(void *void_philo);
int			death_check(t_rules *rules);
void		lets_eat(t_philo *philo);

#endif
