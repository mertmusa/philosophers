/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:31:08 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/07 10:50:34 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_continue2(t_rules *rules)
{
	sem_unlink("./writs");
	sem_unlink("./forks");
	rules->forks = sem_open("./forks", O_CREAT, S_IRWXG, rules->philo_nof);
	rules->writs = sem_open("./writs", O_CREAT, S_IRWXG, 1);
	if (rules->forks == SEM_FAILED || rules->writs == SEM_FAILED)
		ft_error("Semaphore(s) did not open properly!");
	return (0);
}

/* continue initializing with philos*/
int	init_continue(t_rules *rules)
{
	int (i) = 0;
	rules->philo = malloc(sizeof(t_philo) * rules->philo_nof);
	if (!rules->philo)
		ft_error("Philo structure allocation error!");
	while (i < rules->philo_nof)
	{
		rules->philo[i].philo_id = i;
		rules->philo[i].eat_counter = 0;
		rules->philo[i].last_eat = get_the_time();
		rules->philo[i].mrules = rules;
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
	return (init_continue(rules));
}
