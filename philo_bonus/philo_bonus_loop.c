/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:54:26 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/07 17:20:33 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->mrules;
	sem_wait(rules->forks);
	my_print(philo->philo_id, "\033[0;91mhas taken right fork🍴", rules);
	sem_wait(rules->forks);
	my_print(philo->philo_id, "\033[0;95mhas taken left fork🍴", rules);
	my_print(philo->philo_id, "\033[0;92mEating 🍕", rules);
	time_passer(philo->mrules->eat_tto, philo->mrules);
	philo->last_eat = get_the_time();
	philo->eat_counter++;
	sem_post(rules->forks);
	sem_post(rules->forks);
}

void	philo_sleep(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->mrules;
	my_print(philo->philo_id, "\033[0;94mSleeping 🌙💤", philo->mrules);
	time_passer(rules->sleep_tto, rules);
}

void	philo_think(t_philo *philo)
{
	my_print(philo->philo_id, "\033[0;93mThinking 💭💭💭", philo->mrules);
}
