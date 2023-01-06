/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:31:08 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/06 14:43:43 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_continue2(t_rules *rules)
{
	int (i) = -1;
	while (++i < rules->philo_nof)
	{
		rules->philo[i].philo_id = i;
		rules->philo[i].eat_counter = 0;
		rules->philo[i].left_fork_id = i;
		rules->philo[i].right_fork_id = (i + 1) % rules->philo_nof;
		rules->philo[i].mrules = rules;
		rules->philo[i].last_eat = get_the_time();
	}
	return (0);
}

/* continue to initialize */
int	init_continue(t_rules *rules)
{
	int (i) = 0;
	while (i < rules->philo_nof)
	{
		if (pthread_mutex_init(&rules->forkex[i], NULL) != 0)
		{
			ft_error("Mutex initialize error!");
			return (1);
		}
		i++;
	}
	rules->philo = malloc (sizeof(t_philo) * rules->philo_nof);
	if (!rules->philo)
	{
		ft_error("Philo structure allocation error!");
		return (1);
	}
	return (init_continue2(rules));
}

/* turn arg to parameters then initialize */
int	argtoparam_init(t_rules *rules, char **argv, int argc)
{
	rules->sleep_tto = ft_atoi(argv[4]);
	rules->eat_tto = ft_atoi(argv[3]);
	rules->die_tto = ft_atoi(argv[2]);
	rules->philo_nof = ft_atoi(argv[1]);
	if (argc == 6)
		rules->eat_noftep = ft_atoi(argv[5]);
	else
		rules->eat_noftep = -1;
	rules->is_dead = 0;
	rules->all_eat = 0;
	rules->start_time = get_the_time();
	pthread_mutex_init(&rules->writex, NULL);
	rules->forkex = malloc (sizeof(pthread_mutex_t) * rules->philo_nof);
	if (!rules->forkex)
	{
		ft_error("Fork mutex allocation error!");
		return (1);
	}
	return (init_continue(rules));
}
