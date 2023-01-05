/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sketch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:20:29 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/05 22:49:57 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//int (deneme) = 0;

//ssymbols: 💀 🍴 🍕 🌙💤 💭💭💭

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

/*int	philo_init(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->mrules;
	printf("this is the line %d ph: %d\n", __LINE__, rules->philo_nof);
	int (i) = 0;
	//rules->philo[i].left_fork_id = rules->philo_nof - 1;
	while (i < rules->philo_nof)
	{
		rules->philo[i].philo_id = i;
		rules->philo[i].right_fork_id = i;
		if (i)
			rules->philo[i].left_fork_id = i - 1;
		rules->philo[i].mrules = rules;
		printf("this is the line %d i: %d\n", __LINE__, i);
		i++;
	}
	return (0);
}*/

/* print acording to rules */
void	my_print(int philo_id, char *s, t_rules *rules)
{
	if(rules->is_dead == 0)
	{
		pthread_mutex_lock(&rules->writex);
		printf("\033[0;97m%llu ", get_the_time() - rules->start_time);
		printf("\033[0;96m%d %s\n", philo_id, s);
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

/* philosophers start to eat */
void	lets_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mrules->forkex[philo->right_fork_id]);
	my_print(philo->philo_id, "\033[0;91mhas taken the right fork 🍴", philo->mrules);
	pthread_mutex_lock(&philo->mrules->forkex[philo->left_fork_id]);
	my_print(philo->philo_id, "\033[0;95mhas taken the left fork 🍴", philo->mrules);
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
					pthread_mutex_destroy(&rules->writex);
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
		if (philo->mrules->eat_noftep > 0 && philo->mrules->eat_noftep <= philo->eat_counter)
		{
			philo->mrules->all_eat = 1;
			break;
		}
		if (philo->mrules->is_dead == 1)
			break;
		my_print(philo->philo_id, "\033[0;94msleeping 🌙💤", philo->mrules);
		time_passer(philo->mrules->sleep_tto, philo->mrules);
		if (philo->mrules->is_dead == 1)
			break;
		my_print(philo->philo_id, "\033[0;93mthinking 💭💭💭", philo->mrules);
	}
	return (NULL);
}

/*void	*routine(void *void_philo)
{
	t_philo	*philo;
	//t_rules	*rules;

	//rules = (t_rules *)void_rules;
	philo = (t_philo *)void_philo;
	//philo->mrules = (t_rules *)malloc(sizeof(t_rules));
	printf("this is the line %d\n", __LINE__);
	printf("this is the line %d philo: %i\n", __LINE__, philo->mrules->philo_nof);
	//philo_init(philo);
	//printf("nof philo:%d\n", philo->mrules->philo_nof);
	printf("this is the line %d\n", __LINE__);
	return (NULL);
}*/

/*void	*routine(void *void_philo)
{
	t_philo	*philo;

	//int (i) = 0;
	philo = (t_philo *)void_philo;
	printf("nof philo:%d\n", philo->mrules->philo_nof);
	(void)philo;
	//philo_init(philo);
	while (i < philo->mrules->philo_nof)
	{
		if (i % 2)
			usleep(10000);
	}
	printf("this is the line %d\n", __LINE__);
	return (NULL);
}*/

/* create threads and send them to table
Note: pthread_create returns 0 on success
if pthread_create does not return 0 write an error! */
int	start_to_thrive(t_rules *rules)
{
	int (i) = -1;
	int (j) = -1;
	while (++i < rules->philo_nof)
	{
		if (pthread_create(&rules->philo[i].thread_id, NULL, routine, &rules->philo[i]) != 0)
			return (1);
		printf("i: %d\n", i);
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

/*void	start_to_thrive(t_rules *rules)
{
	int (i) = 0;
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
}*/

/* continue to initialize */
int	init_continue(t_rules *rules)
{
	int (i) = 0;
	while (i < rules->philo_nof)
	{
		if (pthread_mutex_init(&rules->forkex[i], NULL) != 0)
		{
			ft_error("Mutex initialize error!");
			return (1);
		}
		//printf("i: %d Mutex initialized!\n", i); //sil
		i++;
	}
	rules->philo = malloc (sizeof(t_philo) * rules->philo_nof);
	if (!rules->philo)
	{
		ft_error("Philo structure allocation error!");
		return (1);
	}
	i = -1;
	while (++i < rules->philo_nof)
	{
		rules->philo[i].philo_id = i;
		rules->philo[i].eat_counter = 0;
		rules->philo[i].left_fork_id = i;
		rules->philo[i].right_fork_id = (i + 1) % rules->philo_nof;
		rules->philo[i].mrules = rules;
		rules->philo[i].last_eat = get_the_time();
	}
	return (0);
}

/* turn arg to parameters then initialize */
int	argtoparam_init(t_rules *rules, char **argv, int argc)
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
	else
		rules->eat_noftep = -1;
	rules->is_dead = 0;
	rules->all_eat = 0;
	rules->start_time = get_the_time();
	//pthread_mutex_init(&rules.writex, NULL);
	rules->forkex = malloc (sizeof(pthread_mutex_t) * rules->philo_nof);
	if (!rules->forkex)
	{
		ft_error("Fork mutex allocation error!");
		return (1);
	}
	return (init_continue(rules));
}

/* continue to check arguments if there is something wrong*/
int	check_arg2(char **argv, int argc)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	{
		ft_error("Number of philo can't be under 1!");
		return (1);
	}
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
	{
		ft_error("Times can not be less than 60ms!");
		return (1);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		ft_error("Number_of_times_each_philosopher_must_eat can't be less than 1!");
		return (1);
	}
	return (0);
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
	return (check_arg2(argv, argc));
}

int	main(int argc, char **argv)
{
	t_rules	*rules;
	//t_philo	*philo;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if (!rules)
	{
		ft_error("Rules structure allocation error!");
		return (0);
	}
	//philo = (t_philo *)malloc(sizeof(t_philo));
	if (argc == 5 || argc == 6)
	{
		if (check_arg(argv, argc))
			return (0);
		if (argtoparam_init(rules, argv, argc))
			return (0);
		if (start_to_thrive(rules))
			return (0);
	}
	else
		ft_error("Wrong Number Of Arguments!");
	return (0);
}
