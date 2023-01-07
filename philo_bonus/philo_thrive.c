/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thrive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:36:55 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/06 15:09:48 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* philosophers start to eat */
void	lets_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mrules->forkex[philo->right_fork_id]);
	my_print(philo->philo_id, "\033[0;91mhas taken right fork 🍴", philo->mrules);
	pthread_mutex_lock(&philo->mrules->forkex[philo->left_fork_id]);
	my_print(philo->philo_id, "\033[0;95mhas taken left fork 🍴", philo->mrules);
	my_print(philo->philo_id, "\033[0;92meating 🍕", philo->mrules);
	philo->last_eat = get_the_time();
	time_passer(philo->mrules->eat_tto, philo->mrules);
	pthread_mutex_unlock(&philo->mrules->forkex[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->mrules->forkex[philo->left_fork_id]);
	philo->eat_counter++;
}

/* check if there is a dead philo */
int	death_check(t_rules *rules)
{
	int (i) = -1;
	int (j) = -1;
	while (rules->all_eat == 0)
	{
		i = -1;
		while (++i < rules->philo_nof)
		{
			if (get_the_time() - rules->philo[i].last_eat > rules->die_tto)
			{
				my_print(rules->philo[i].philo_id, "\033[0;91mdied 💀", rules);
				rules->is_dead = 1;
				if (rules->philo_nof == 1)
				{
					pthread_mutex_destroy(&rules->writex);
					while (++j < rules->philo_nof)
						pthread_mutex_destroy(&rules->forkex[j]);
					return (1);
				}
			}
		}
		if (rules->is_dead == 1)
			return (1);
	}
	return (0);
}

/* function is called by thread creation */
void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->philo_id % 2)
		usleep(1000);
	while (philo->mrules->is_dead == 0)
	{
		if (philo->mrules->is_dead == 1)
			break ;
		lets_eat(philo);
		if (philo->mrules->eat_noftep > 0
			&& philo->mrules->eat_noftep <= philo->eat_counter)
		{
			philo->mrules->all_eat = 1;
			break ;
		}
		if (philo->mrules->is_dead == 1)
			break ;
		my_print(philo->philo_id, "\033[0;94msleeping 🌙💤", philo->mrules);
		time_passer(philo->mrules->sleep_tto, philo->mrules);
		if (philo->mrules->is_dead == 1)
			break ;
		my_print(philo->philo_id, "\033[0;93mthinking 💭💭💭", philo->mrules);
	}
	return (NULL);
}

/* create threads and send them to table
Note: pthread_create returns 0 on success
if pthread_create does not return 0 write an error! */
int	start_to_thrive(t_rules *rules)
{
	int (i) = -1;
	int (j) = -1;
	while (++i < rules->philo_nof)
	{
		if (pthread_create(&rules->philo[i].thread_id,
				NULL, routine, &rules->philo[i]) != 0)
			return (1);
	}
	if (death_check(rules))
		return (1);
	while (++j < rules->philo_nof)
		pthread_join(rules->philo[j].thread_id, NULL);
	j = -1;
	while (++j < rules->philo_nof)
		pthread_mutex_destroy(&rules->forkex[j]);
	pthread_mutex_destroy(&rules->writex);
	return (0);
}
