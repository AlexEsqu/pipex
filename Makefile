# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 14:56:12 by mkling            #+#    #+#              #
#    Updated: 2025/11/01 18:30:09 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

SRC_DIR		= src

INC_DIR		= inc

OBJ_DIR		= obj

TMP_DIR		= tmp

SRC			= heredoc.c  index.c  main.c  parsing.c  pipe.c  readability.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))

LIB			= $(INC_DIR)/libft/libft.a

HEADER		= $(INC_DIR)/pipex.h

OBJ			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			= cc

CFLAGS		= -Wall -Wextra -Werror


all:		$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ)
			$(MAKE) -C $(INC_DIR)/libft
			$(CC) $(CFLAGS) -I$(INC_DIR) -I$(INC_DIR)/libft $(OBJ) -o $(NAME) $(LIB)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					mkdir -p $(TMP_DIR)
					$(CC) $(CFLAGS)  -I$(INC_DIR)  -I$(INC_DIR)/libft/inc -c $< -o $@

$(OBJ_DIR):
					mkdir -p $@

debug:
			$(MAKE) -C $(INC_DIR)/libft
			$(CC) $(CFLAGS) -g3 -I$(INC_DIR) $(SRCS) -o $(NAME)

clean:
			rm -rf $(OBJ_DIR)
			rm -rf $(TMP_DIR)
			$(MAKE) -C $(INC_DIR)/libft clean

fclean:		clean
			rm -rf pipex
			$(MAKE) -C $(INC_DIR)/libft fclean

re:			fclean all

.PHONY:		all clean fclean re debug
