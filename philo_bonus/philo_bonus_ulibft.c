/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_ulibft.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:19:40 by mtemel            #+#    #+#             */
/*   Updated: 2023/01/07 10:19:03 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*string to int*/
int	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			pos;
	char		*s;

	pos = 1;
	i = 0;
	res = 0;
	s = (char *)str;
	while (s[i] == ' ' || (s[i] > 8 && s[i] < 14))
		i++;
	if (s[i] == '+' || s[i] == '-')
		pos = 1 - 2 * (s[i++] == '-');
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 +(s[i++] - 48);
		if (res > 2147483647 && pos == 1)
			return (-1);
		else if (res > 2147483648 && pos == -1)
			return (0);
	}
	return ((int)(res * pos));
}

/*is character a digit*/
int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	else
		return (1);
}
