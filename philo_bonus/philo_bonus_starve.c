/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_starve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:36:55 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/07 17:25:17 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_check(void *void_philo)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)void_philo;
	rules = philo->mrules;
	while (1)
	{
		if (philo->eat_counter == rules->eat_noftep)
			break ;
		if (get_the_time() - philo->last_eat > rules->die_tto)
		{
			my_print(philo->philo_id, "\033[0;91mPhilosoph died 💀", rules);
			rules->is_dead = 1;
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}

/* function is called by thread creation */
void	spawn(t_philo *philo)
{
	if (philo->philo_id % 2)
		usleep(1000);
	philo->last_eat = get_the_time();
	pthread_create(&philo->mrules->yep, NULL, death_check, philo);
	while (philo->mrules->is_dead == 0)
	{
		philo_eat(philo);
		if (philo->eat_counter == philo->mrules->eat_noftep)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	exit(1);
}

void	*waitp(void *data)
{
	int		i;
	int		res;
	t_rules	*rules;

	i = -1;
	rules = (t_rules *)data;
	while (1)
	{
		waitpid(-1, &res, 0);
		if (res != 0)
		{
			while (++i < rules->philo_nof)
				kill(rules->philo[i].process_id, SIGKILL);
			break ;
		}
		usleep(100);
	}
	sem_close(rules->forks);
	sem_close(rules->writs);
	sem_unlink("./forks");
	sem_unlink("./writs");
	return (NULL);
}

/* create threads and send them to table
Note: pthread_create returns 0 on success
if pthread_create does not return 0 write an error! */
int	start_to_starve(t_rules *rules)
{
	int (i) = -1;
	while (++i < rules->philo_nof)
	{
		rules->philo[i].process_id = fork();
		if (rules->philo[i].process_id < 0)
			ft_error("Fork didn't open properly");
		if (rules->philo[i].process_id == 0)
			spawn(&rules->philo[i]);
		usleep(100);
	}
	pthread_create(&rules->check, NULL, waitp, rules);
	pthread_join(rules->check, NULL);
	return (0);
}
