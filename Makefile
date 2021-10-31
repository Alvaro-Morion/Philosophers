# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorion- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 11:19:21 by amorion-          #+#    #+#              #
#    Updated: 2021/10/22 11:19:23 by amorion-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c philos.c utils.c

OBJS = ${SRCS:.c=.o}

NAME = philo

all: ${NAME}

.c.o:
	@gcc -Wall -Werror -Wextra -pthread -g -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@gcc -Wall -Werror -Wextra -pthread -g ${OBJS} -o ${NAME}
	@echo "binary generated"
clean:
	@echo "o files deleted"
	@rm -rf ${OBJS}
fclean: clean
	@echo "philo deleted"
	@rm -rf ${NAME}
re: fclean all