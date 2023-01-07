/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:24:22 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/07 17:17:33 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
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

//philo_bonus_ulibft
int			ft_atoi(const char *str);
int			ft_isdigit(int c);

//philo_bonus_utils
void		ft_error(char *str);
long long	get_the_time(void);
void		my_print(int philo_id, char *s, t_rules *rules);
void		time_passer(int time_tocheck, t_rules *rules);

//philo_bonus_init
int			argtoparam_init(t_rules *rules, char **argv, int argc);
int			init_continue(t_rules *rules);
int			init_continue2(t_rules *rules);

//philo_bonus_check
int			check_arg(char **argv, int argc);
int			check_arg2(char **argv, int argc);

//philo_bonus_loop
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

//💀 🍴 🍕 🌙💤 💭💭💭
int			start_to_starve(t_rules *rules);
void		*waitp(void *data);
void		spawn(t_philo *philo);
void		*death_check(void *void_philo);

#endif
