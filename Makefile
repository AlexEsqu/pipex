# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 14:56:12 by mkling            #+#    #+#              #
#    Updated: 2025/11/01 18:35:57 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

SRC_DIR		= src

INC_DIR		= inc

OBJ_DIR		= obj

TMP_DIR		= tmp

SRC			= heredoc.c  index.c  main.c  parsing.c  pipe.c  readability.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))

LIB			= $(INC_DIR)/libft

HEADER		= $(INC_DIR)/pipex.h

OBJ			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

INC			= -I$(INC_DIR)  -I$(INC_DIR)/libft/inc


all:		$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ)
			$(MAKE) -C $(LIB)
			$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIB)/libft.a -o $(NAME)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					mkdir -p $(TMP_DIR)
					$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
					mkdir -p $@

debug:
			$(MAKE) -C $(LIB)
			$(CC) $(CFLAGS) -g3 $(INC) $(SRCS) $(LIB)/libft.a -o $(NAME)

clean:
			rm -rf $(OBJ_DIR)
			rm -rf $(TMP_DIR)
			$(MAKE) -C $(LIB) clean

fclean:		clean
			rm -rf pipex
			$(MAKE) -C $(LIB) fclean

re:			fclean all

.PHONY:		all clean fclean re debug
