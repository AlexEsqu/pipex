# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 10:20:10 by alex              #+#    #+#              #
#    Updated: 2025/11/01 18:25:22 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

DIR_INC	= inc

DIR_SRC = src

DIR_OBJ	= obj

HEADER	= $(DIR_INC)/libft.h

SRC 	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memmove.c \
		ft_memset.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strjoin.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_substr.c ft_tolower.c ft_tuupper.c ft_memcmp.c \
		ft_memchr.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c get_next_input.c ft_free_tab.c

SRCS	= $(addprefix $(DIR_SRC)/, $(SRC))

OBJS	= $(SRCS:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

DEP		= $(DIR_OBJ) $(HEADER)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

INC		= -I$(DIR_INC)


all:				$(NAME)

$(NAME):			$(DIR_OBJ) $(OBJS)
					ar rcs $(NAME) $(OBJS)

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c $(HEADER)
					$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(DIR_OBJ):
					mkdir -p $@

clean:
					rm -rf $(DIR_OBJ)

fclean:				clean
					rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
