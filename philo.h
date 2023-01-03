/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:24:22 by mtemel            #+#    #+#             */
/*   Updated: 2022/12/27 12:51:46 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct	s_rules t_rules;
typedef struct s_philo
{
	int				philo_id;
	int				left_fork_id;
	int				right_fork_id;
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
	t_philo			philo[250];
	pthread_mutex_t	forks[250];
}	t_rules;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);

#endif
