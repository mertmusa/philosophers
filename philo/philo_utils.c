/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:10:56 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/06 14:14:02 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* warn when there is an error and write the description */
void	ft_error(char *str)
{
	write(2, "Error!\n", 7);
	printf("%s\n", str);
}

/* time from system */
long long	get_the_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)1000 * (tv.tv_sec)) + ((tv.tv_usec) / (long long)1000));
}

/* print acording to rules */
void	my_print(int philo_id, char *s, t_rules *rules)
{
	if(rules->is_dead == 0)
	{
		pthread_mutex_lock(&rules->writex);
		printf("\033[0;97m%llu \033[0;96m%d %s\n", get_the_time() - rules->start_time, philo_id, s);
		pthread_mutex_unlock(&rules->writex);
	}
}

/* pass the time acording to arguments */
void	time_passer(int time_tocheck, t_rules *rules)
{
	long long start;

	start = get_the_time();
	while (rules->is_dead == 0)
	{
		if (get_the_time() - start >= time_tocheck)
			break;
		usleep(41);
	}
}