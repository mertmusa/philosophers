/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:20:29 by mtemel            #+#    #+#             */
/*   Updated: 2022/12/26 17:16:32 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* warn when there is an error and write the description */
void	ft_error(char *str)
{
	write(2, "Error!\n", 7);
	printf("%s\n", str);
}

void	*routine()
{
	printf("Test from thread!\n");
	return (0);
}

/* create threads
Note: pthread_create returns 0 on success
if pthread_create does not return 0 write an error! */
void	create_thread(t_philo *philo, t_thread *thread)
{
	int	i;

	(void)thread;
	i = 0;
	while (i < philo->philo_nof)
	{
		if (pthread_create(&philo->mythread[i].thread_id, NULL, &routine, NULL) != 0)
		{
			printf("Create error thread no:%d\n", i);
			ft_error("Thread creation error!");
		}
		if (pthread_join(philo->mythread[i].thread_id, NULL) != 0)
		{
			printf("Join error thread no:%d\n", i);
			ft_error("Thread join error!");
		}
		i++;
	}
}

/* start of hunger games */
void	start_to_thrive(t_philo *philo, t_thread *thread)
{
	create_thread(philo, thread);
}

/* check arguments if there is nothing wrong then take as parameters */
void	check_then_argtoparam(t_philo *philo, t_thread *thread, char **argv, int c)
{
	int	i;
	int	j;

	(void)thread;
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
	if (philo->philo_nof < 1)
		ft_error("Number of philo can't be under 1!");
	if (philo->sleep_tto < 0 || philo->eat_tto < 0 || philo->die_tto < 0 || philo->eat_noftep < 0)
		ft_error("Times can not be negative!");
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_thread	*thread;

	philo = (t_philo *)malloc(sizeof(t_philo));
	thread = (t_thread *)malloc(sizeof(t_thread));
	if (argc == 5 || argc == 6)
	{
		check_then_argtoparam(philo, thread, argv, argc);
		start_to_thrive(philo, thread);
	}
	else
		ft_error("Wrong Number Of Arguments!");
}
