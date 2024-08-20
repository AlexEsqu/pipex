# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkling <mkling@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 14:56:12 by mkling            #+#    #+#              #
#    Updated: 2024/08/19 13:24:38 by mkling           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

SRC_DIR		= ./src

BUILD_DIR	= ./build

BIN_DIR		= ./build/bin

OBJ_DIR		= ./build/obj

LIB_DIR		= ./lib/libft/

SRCS		= $(wildcard $(SRC_DIR)/*.c)

LIBS		= ./lib/libft/libft.a

OBJS		= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CC			= cc

CFLAGS		= -Wall -Wextra -Werror


all:		${NAME}

${NAME}:	${OBJS} library
			mkdir -p $(BUILD_DIR)
			mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBS)

library:
			$(MAKE) -C ./lib/libft

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					mkdir -p $(OBJ_DIR)
					$(CC) $(CFLAGS) $(foreach dir,$(LIB_DIR), -I$(dir)) -c $< -o $@

debug:		${OBJS} library
			$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) $(LIBS)

clean:
			rm -rf $(OBJ_DIR)
			$(MAKE) -C ./lib/libft clean

fclean:		clean
			rm -rf $(BIN_DIR)
			$(MAKE) -C ./lib/libft fclean

re:			fclean all

.PHONY:		all clean fclean re
