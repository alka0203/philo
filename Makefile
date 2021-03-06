# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 11:32:22 by asanthos          #+#    #+#              #
#    Updated: 2022/05/05 08:27:42 by asanthos         ###   ########.fr        #
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

CC = @gcc -pthread

CFLAGS = -Wall -Werror -Wextra -pthread -ggdb

RM = @rm -rf

POST = "\e[1;95mLet the eating commence!\n"

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)


all:	${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: 	fclean all
		@printf ${POST}

.PHONY = all clean fclean re
