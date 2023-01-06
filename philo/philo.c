/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:09:52 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/06 14:38:26 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if (!rules)
	{
		ft_error("Rules structure allocation error!");
		return (0);
	}
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
