# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 11:32:22 by asanthos          #+#    #+#              #
#    Updated: 2022/04/29 14:04:57 by asanthos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	./srcs/parser.c		\
		./srcs/helpers.c	\
		./srcs/main.c		\
		./srcs/philo_init.c	\
		./srcs/threads.c	\
		./srcs/mut.c		\
		./srcs/tasks.c		\
		./srcs/sleep.c		\
		./srcs/free.c		\
		./srcs/time.c		\
		./srcs/eat.c		\
		./srcs/death.c		\
		./srcs/forks.c		\
		./srcs/args_check.c	\

OBJS = ${SRCS:.c=.o}

CC = gcc -pthread

CFLAGS = -Wall -Werror -Wextra -pthread -ggdb

RM = rm -rf

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

all:	${NAME}	

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: 	fclean all
