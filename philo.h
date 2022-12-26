/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:24:22 by mtemel            #+#    #+#             */
/*   Updated: 2022/11/30 16:38:09 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	int	philo_nof;
	int	die_tto;
	int	eat_tto;
	int	sleep_tto;
	int	eat_noftep;
}	t_philo;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);

#endif
