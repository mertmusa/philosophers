/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:20:29 by mtemel            #+#    #+#             */
/*   Updated: 2022/11/30 17:14:30 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* warn when there is an error and write the description */
void	ft_error(char *str)
{
	write(2, "Error!\n", 7);
	printf("%s\n", str);
}

/* create threads
Note: pthread_create returns 0 on success
if pthread_create does not return 0 write an error! */
void	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_nof)
	{
		if (!pthread_create())
			ft_error("Thread creation error!");
		i++;
	}
}

/* start of hunger games */
void	start_to_thrive(t_philo *philo)
{
	create_thread(philo);
}

/* check arguments if there is nothing wrong then take as parameters */
void	check_then_argtoparam(t_philo *philo, char **argv, int c)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				ft_error("Arguments contain non-digit value!");
				return ;
			}
			j++;
		}
		i++;
	}
	philo->sleep_tto = ft_atoi(argv[4]);
	philo->eat_tto = ft_atoi(argv[3]);
	philo->die_tto = ft_atoi(argv[2]);
	philo->philo_nof = ft_atoi(argv[1]);
	printf("number_of_philosophers: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep: %d\n", philo->philo_nof, philo->die_tto, philo->eat_tto, philo->sleep_tto);
	if (c == 6)
	{
		philo->eat_noftep = ft_atoi(argv[5]);
		printf("number_of_times_each_philosopher_must_eat: %d\n", philo->eat_noftep);
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (argc == 5 || argc == 6)
	{
		check_then_argtoparam(philo, argv, argc);
		start_to_thrive(philo);
	}
	else
		ft_error("Wrong Number Of Arguments!");
}
