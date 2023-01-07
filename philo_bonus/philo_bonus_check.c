/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:34:34 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/07 10:19:11 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		ft_error("Number_of_eat can't be less than 1!");
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
