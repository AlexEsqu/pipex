# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkling <mkling@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 14:56:12 by mkling            #+#    #+#              #
#    Updated: 2024/09/08 17:51:52 by mkling           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

SRC_DIR		= ./src

SRC_B_DIR	= ./src_bonus

BIN_DIR		= ./bin

TMP_DIR		= ./tmp

LIB_DIR		= ./lib/libft

SRCS		= $(wildcard $(SRC_DIR)/*.c)

SRCS_B		= $(wildcard $(SRC_B_DIR)/*.c) $(filter-out src/pipex.c, $(wildcard src/*.c))

LIBS		= ./lib/libft/libft.a

OBJS		= $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

CC			= cc

CFLAGS		= -Wall -Wextra -Werror


all:		${NAME}

${NAME}:	${OBJS}
			$(MAKE) -C ./lib/libft
			$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBS)

$(BIN_DIR)/%.o:		$(SRC_DIR)/%.c
					mkdir -p $(BIN_DIR)
					mkdir -p $(TMP_DIR)
					$(CC) $(CFLAGS) $(foreach dir,$(LIB_DIR), -I$(dir)) -c $< -o $@

bonus:		${OBJS}
			$(MAKE) -C ./lib/libft
			$(CC) $(CFLAGS) -o pipex_bonus $(SRCS_B) $(LIBS)

debug:		${OBJS}
			$(MAKE) -C ./lib/libft
			$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) $(LIBS)

clean:
			rm -rf $(BIN_DIR)
			$(MAKE) -C ./lib/libft clean

fclean:		clean
			rm -rf pipex
			$(MAKE) -C ./lib/libft fclean

re:			fclean all

.PHONY:		all clean fclean re debug
