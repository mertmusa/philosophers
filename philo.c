/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:20:29 by mtemel            #+#    #+#             */
/*   Updated: 2022/12/27 12:15:12 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int (deneme) = 0;

/* warn when there is an error and write the description */
void	ft_error(char *str)
{
	write(2, "Error!\n", 7);
	printf("%s\n", str);
}

void	*routine()
{
	int (i) = 0;
	while(i < 1000000)
	{
		/*pthread_mutex_lock(&philo->forks);*/
		deneme++;
		i++;
		/*pthread_mutex_lock(&mutex);*/
	}
	return (NULL);
}

/* create threads and send them to table
Note: pthread_create returns 0 on success
if pthread_create does not return 0 write an error! */
void	start_to_thrive(t_philo *philo, t_thread *thread)
{
	int	i;

	(void)thread;
	i = 0;
	printf("Mutex init error mutex no:%d\n", i);
	while (i < philo->philo_nof)
	{
		if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
		{
			printf("Mutex init error mutex no:%d\n", i);
			ft_error("Mutex init error!");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < philo->philo_nof)
	{
		if (pthread_create(&philo->mythread[i].thread_id, NULL, &routine, NULL) != 0)
		{
			printf("Create error thread no:%d\n", i);
			ft_error("Thread creation error!");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < philo->philo_nof)
	{
		if (pthread_join(philo->mythread[i].thread_id, NULL) != 0)
		{
			printf("Join error thread no:%d\n", i);
			ft_error("Thread join error!");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < philo->philo_nof)
	{
		if (pthread_mutex_destroy(&philo->forks[i]) != 0)
		{
			printf("Mutex destroy mutex no:%d\n", i);
			ft_error("Mutex destroy error!");
			return ;
		}
		i++;
	}
}

/* turn arg to parameters */
void	argtoparam(t_philo *philo, char **argv, int argc)
{
	philo->sleep_tto = ft_atoi(argv[4]);
	philo->eat_tto = ft_atoi(argv[3]);
	philo->die_tto = ft_atoi(argv[2]);
	philo->philo_nof = ft_atoi(argv[1]);
	printf("number_of_philosophers: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep: %d\n", philo->philo_nof, philo->die_tto, philo->eat_tto, philo->sleep_tto);
	if (argc == 6)
	{
		philo->eat_noftep = ft_atoi(argv[5]);
		printf("number_of_times_each_philosopher_must_eat: %d\n", philo->eat_noftep);
	}
}

/* check arguments if there is something wrong*/
int	check_arg(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if(j == 0 && argv[i][j] == '-')
				j++;
			if (!ft_isdigit(argv[i][j]))
			{
				ft_error("Arguments contain non-digit value!");
				return (1);
			}
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	{
		ft_error("Number of philo can't be under 1!");
		return (1);
	}
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
	{
		ft_error("Times can not be negative!");
		return (1);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		ft_error("Number_of_times_each_philosopher_must_eat can't be less than 1!");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_thread	*thread;

	philo = (t_philo *)malloc(sizeof(t_philo));
	thread = (t_thread *)malloc(sizeof(t_thread));
	philo->deneme = 0;
	if (argc == 5 || argc == 6)
	{
		if(check_arg(argv, argc))
			return (0);
		argtoparam(philo, argv, argc);
		start_to_thrive(philo, thread);
		printf("deneme: %d\n", deneme);
	}
	else
		ft_error("Wrong Number Of Arguments!");
	return (0);
}
