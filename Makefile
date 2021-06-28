# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungoh <seungoh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/27 23:27:06 by seungoh           #+#    #+#              #
#    Updated: 2021/06/28 06:20:26 by seungoh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OUT			=		philo
CC			= 		gcc
CFLAGS		=		-Wall -Werror -Wextra
SRCS		=		main.c\
					utils.c\
					parsing.c
OBJS		=		${SRCS:.c=.o}

all			:		${OUT}

.c.o		:
		${CC} ${CFLAGS} -c ${<} -o ${<:.c=.o}

${OUT}		: ${OBJS}
		${CC} ${CFLAGS} -o ${OUT} ${OBJS}

clean		:
		rm -rf ${OBJS}

fclean		: clean
		rm -rf ${OUT}

re			:	fclean all

.PHONY		: all clean fclean re