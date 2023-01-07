/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_thrive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:36:55 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/07 11:10:11 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* philosophers start to eat */
/*void	lets_eat(t_philo *philo)
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
}*/

/* check if there is a dead philo */
/*int	death_check(t_rules *rules)
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
}*/

/*void	*hospital(void *data)
{
	t_phis	*philo;
	t_state	*all;

	philo = (t_phis *)data;
	all = philo->link;
	while (true)
	{
		if (philo->eat_count == all->must_eat)
			break ;
		if (gettime() - philo->last_eat > all->time_die)
		{
			print(philo->id, "\033[0;91mPhilosop died", all);
			all->is_died = true;
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}*/

/*void	meal_time(t_phis *philo)
{
	t_state	*all;

	all = philo->link;
	sem_wait(all->forks);
	print(philo->id, "\033[0;91mtook the right fork", all);
	sem_wait(all->forks);
	print(philo->id, "\033[0;95mtook the left fork", all);
	print(philo->id, "\033[0;92mEating", all);
	pass_the_time(philo->link->time_eat, philo->link);
	philo->last_eat = gettime();
	philo->eat_count++;
	sem_post(all->forks);
	sem_post(all->forks);
}

void	philo_sleep(t_phis *philo)
{
	t_state	*all;

	all = philo->link;
	print(philo->id, "\033[0;94mSleeping", philo->link);
	pass_the_time(all->time_sleep, all);
}

void	philo_think(t_phis *philo)
{
	print(philo->id, "\033[0;93mThinking", philo->link);
}*/


/* function is called by thread creation */
void	spawn(t_philo *philo)
{
	if (philo->philo_id % 2)
		usleep(1000);
	philo->last_eat = get_the_time();
	pthread_create(&philo->mrules->yep, NULL, hospital, philo);
	while (philo->mrules->is_dead == 0)
	{
		philo_eat(philo);
		if (philo->eat_counter == philo->mrules->eat_noftep)
			break;
		philo_sleep(philo);
		philo_think(philo);
	}
	exit(1);
}

/* create threads and send them to table
Note: pthread_create returns 0 on success
if pthread_create does not return 0 write an error! */
int	start_to_thrive(t_rules *rules)
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
