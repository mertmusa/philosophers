# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 16:21:03 by mtemel            #+#    #+#              #
#    Updated: 2023/01/06 14:13:20 by mtemel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRCS = philo*.c
OBJ = $(SRCS:.c = .o)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(SRCS) -o $(NAME)
	@echo "\033[1;92mCOMPILED SUCCESSFULLY...\033[0m"

all: $(NAME)

clean:
	@rm -f $(NAME)
	@echo "\033[1;92mCLEAN...\033[0m"

fclean:
	@echo "\033[1;92mFCLEAN...\033[0m"
	@make clean

re:
	@echo "\033[1;92mREMAKE...\033[0m"
	@make fclean
	@make all

.PHONY: all clean fclean re bonus
