/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:10:56 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/07 11:12:30 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* warn when there is an error and write the description */
void	ft_error(char *str)
{
	write(2, "Error!\n", 7);
	printf("%s\n", str);
	exit(EXIT_FAILURE);
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
	if (rules->is_dead == 0)
	{
		pthread_mutex_lock(&rules->writex);
		printf("\033[0;97m%llu \033[0;96m%d %s\n",
			get_the_time() - rules->start_time, philo_id, s);
		pthread_mutex_unlock(&rules->writex);
	}
}

/* pass the time acording to arguments */
void	time_passer(int time_tocheck, t_rules *rules)
{
	long long	start;

	start = get_the_time();
	while (rules->is_dead == 0)
	{
		if (get_the_time() - start >= time_tocheck)
			break ;
		usleep(41);
	}
}

/*void	*waitp(void *data)
{
	int		idx;
	int		res;
	t_state	*all;

	idx = -1;
	all = (t_state *)data;
	while (true)
	{
		waitpid(-1, &res, 0);
		if (res != 0)
		{
			while (++idx < all->number_of)
				kill(all->philo[idx].pid, SIGKILL);
			break ;
		}
		usleep(100);
	}
	sem_close(all->forks);
	sem_close(all->print);
	sem_unlink("./forks");
	sem_unlink("./print");
	return (NULL);
}*/
