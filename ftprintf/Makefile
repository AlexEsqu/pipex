# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkling <mkling@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 10:20:10 by mkling            #+#    #+#              #
#    Updated: 2024/08/14 11:27:28 by mkling           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

SRCS		= printf_buffering.c printf_print.c \
			printf_parsing_int.c printf_parsing_str.c

LIB_DIR		= ../libft/

OBJS		= ${SRCS:.c=.o}

CC			= cc

CFLAGS		= -Wall -Wextra -Werror



all:		${NAME}

${NAME}:	library ${OBJS}
			ar rcs ${NAME} ${OBJS} $(LIB_DIR)*.o

library:
			$(MAKE) -C $(LIB_DIR)

%.o:	 	%.c
			$(CC) $(CFLAGS) -I$(LIB_DIR) -c $<

clean:
			rm -f $(OBJS) $(BOBJS)
			$(MAKE) -C $(LIB_DIR) clean

fclean:		clean
			rm -f $(NAME)
			$(MAKE) -C $(LIB_DIR) fclean

re:			fclean all

.PHONY:		all clean fclean re
