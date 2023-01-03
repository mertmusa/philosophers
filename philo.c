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

//int (deneme) = 0;

/* warn when there is an error and write the description */
void	ft_error(char *str)
{
	write(2, "Error!\n", 7);
	printf("%s\n", str);
}

int	philo_init(t_philo *philo)
{
	t_rules *rules;

	rules = philo->mrules;
	int (i) = 0;
	rules->philo[i].left_fork_id = rules->philo_nof - 1;
	while (i < rules->philo_nof)
	{
		rules->philo[i].philo_id = i;
		rules->philo[i].right_fork_id = i;
		if (i)
			rules->philo[i].left_fork_id = i - 1;
		rules->philo[i].mrules = rules;
	}
	return (0);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	int (i) = 0;
	philo = (t_philo *)void_philo;
	philo_init(philo);
	while (i < philo->mrules->philo_nof)
	{
		if (i % 2)
			usleep(10000);
	}
	return (NULL);
}

/* create threads and send them to table
Note: pthread_create returns 0 on success
if pthread_create does not return 0 write an error! */
void	start_to_thrive(t_rules *rules, t_philo *philo)
{
	int	i;

	(void)philo;
	i = 0;
	while (i < rules->philo_nof)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
		{
			printf("Mutex init error mutex no:%d\n", i);
			ft_error("Mutex init error!");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < rules->philo_nof)
	{
		if (pthread_create(&rules->philo[i].thread_id, NULL, &routine, (void *)(&rules->philo[i])) != 0)
		{
			printf("Create error thread no:%d\n", i);
			ft_error("Thread creation error!");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < rules->philo_nof)
	{
		if (pthread_join(rules->philo[i].thread_id, NULL) != 0)
		{
			printf("Join error thread no:%d\n", i);
			ft_error("Thread join error!");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < rules->philo_nof)
	{
		if (pthread_mutex_destroy(&rules->forks[i]) != 0)
		{
			printf("Mutex destroy mutex no:%d\n", i);
			ft_error("Mutex destroy error!");
			return ;
		}
		i++;
	}
}

/* turn arg to parameters */
void	argtoparam_init(t_rules *rules, char **argv, int argc)
{
	rules->sleep_tto = ft_atoi(argv[4]);
	rules->eat_tto = ft_atoi(argv[3]);
	rules->die_tto = ft_atoi(argv[2]);
	rules->philo_nof = ft_atoi(argv[1]);
	printf("number_of_philosophers: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep: %d\n", rules->philo_nof, rules->die_tto, rules->eat_tto, rules->sleep_tto);
	if (argc == 6)
	{
		rules->eat_noftep = ft_atoi(argv[5]);
		printf("number_of_times_each_philosopher_must_eat: %d\n", rules->eat_noftep);
	}
	rules->is_dead = 0;
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
			if (j == 0 && argv[i][j] == '-')
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
	t_rules	*rules;
	t_philo	*philo;

	rules = (t_rules *)malloc(sizeof(t_rules));
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (argc == 5 || argc == 6)
	{
		if (check_arg(argv, argc))
			return (0);
		argtoparam_init(rules, argv, argc);
		start_to_thrive(rules, philo);
	}
	else
		ft_error("Wrong Number Of Arguments!");
	return (0);
}
