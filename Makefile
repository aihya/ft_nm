# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/28 16:28:57 by aihya             #+#    #+#              #
#    Updated: 2022/06/11 16:48:05 by aihya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = ft_nm

SRC_NAME =	hashtable.c \
			elf64.c \
			elf32.c \
			main.c

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CFLAGS = #-Wall \
		 -Werror \
		 -Wextra

INCLUDE =	-Iinc \
			-Ilibft/include

HEADER	= ./inc/ft_nm.h

all : $(NAME)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEADER)
	@mkdir -p $(OBJ_PATH) 
	gcc $(CFLAGS) $(INCLUDE) -Llibft -lft -o $@ -c $<

libft_all:
	make -C libft

$(NAME): libft_all $(OBJ)
	gcc $(OBJ) -Llibft -lft  -o $@

clean :
	make -C libft clean
	/bin/rm -rf $(OBJ_PATH) 2> /dev/null

fclean : clean
	make -C libft fclean
	/bin/rm -f $(NAME)

re : fclean all
