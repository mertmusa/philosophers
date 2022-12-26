# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 16:21:03 by mtemel            #+#    #+#              #
#    Updated: 2022/11/28 16:28:45 by mtemel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	gcc -Wall -Wextra -Werror philo*.c -o philo

clean:
	rm -f philo

fclean: clean

re: fclean all

.PHONY: all clean fclean re bonus
