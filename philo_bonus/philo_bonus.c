/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:09:52 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/07 17:18:43 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if (!rules)
		ft_error("Rules structure allocation error!");
	if (argc == 5 || argc == 6)
	{
		check_arg(argv, argc);
		argtoparam_init(rules, argv, argc);
		start_to_starve(rules);
	}
	else
		ft_error("Wrong Number Of Arguments!");
	return (0);
}
