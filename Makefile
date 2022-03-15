# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 11:32:22 by asanthos          #+#    #+#              #
#    Updated: 2022/03/15 14:19:59 by asanthos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	./srcs/philo.c		\
		./srcs/parser.c		\
		./srcs/helpers.c	\
		./srcs/test.c		\

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread

RM = rm -rf

$(NAME): ${OBJS}
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all:	${NAME}	

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: 	fclean all
