# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkling <mkling@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 14:56:12 by mkling            #+#    #+#              #
#    Updated: 2024/08/14 16:24:56 by mkling           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

SRC_DIR		= ./src

BIN_DIR		= ./build/bin

OBJ_DIR		= ./build/obj

LIB_DIR		= ./lib/libft/ ./lib/libftprintf/

SRCS		= $(wildcard $(SRC_DIR)/*.c)

LIBS		= ./lib/libft/libft.a ./lib/libftprintf/libftprintf.a

OBJS		= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CC			= cc

CFLAGS		= -Wall -Wextra -Werror


all:		${NAME}

test:
			@echo $(OBJS)

${NAME}:	${OBJS} library
			$(CC) $(CFLAGS) -o $(BIN_DIR)/$(NAME) $(SRCS) $(LIBS)

library:
			$(MAKE) -C ./lib/libft
			$(MAKE) -C ./lib/libftprintf

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					mkdir -p $(OBJ_DIR)
					$(CC) $(CFLAGS) $(foreach dir,$(LIB_DIR), -I$(dir)) -c $< -o $@

clean:
			rm -f $(OBJS) $(BOBJS)
			$(MAKE) -C ./lib/libft clean
			$(MAKE) -C ./lib/libftprintf clean

fclean:		clean
			rm -f $(BIN_DIR)/$(NAME)
			$(MAKE) -C ./lib/libft fclean
			$(MAKE) -C ./lib/libftprintf fclean

re:			fclean all

.PHONY:		all clean fclean re
