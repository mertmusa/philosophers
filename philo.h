/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:24:22 by mtemel            #+#    #+#             */
/*   Updated: 2022/12/26 17:02:08 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

struct	s_philo;

typedef struct s_thread
{
	int				philo_id;
	int				left_fork_id;
	int				right_fork_id;
	pthread_t		thread_id;
	pthread_t		fork_id;
	struct s_philo	*myphilo;
}	t_thread;

typedef struct s_philo
{
	int			philo_nof;
	int			die_tto;
	int			eat_tto;
	int			sleep_tto;
	int			eat_noftep;
	t_thread	mythread[500];
}	t_philo;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);

#endif
