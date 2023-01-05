/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:24:22 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/05 17:22:27 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_rules;
typedef struct s_philo
{
	int				philo_id;
	int				left_fork_id;
	int				right_fork_id;
	int				eat_counter;
	long long		last_eat;
	pthread_t		thread_id;
	struct s_rules	*mrules;
}	t_philo;

typedef struct s_rules
{
	int				philo_nof;
	int				die_tto;
	int				eat_tto;
	int				sleep_tto;
	int				eat_noftep;
	int				is_dead;
	int				all_eat;
	pthread_mutex_t	*forkex;
	pthread_mutex_t	writex;
	t_philo			*philo;
	long long		start_time;
}	t_rules;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);

#endif
