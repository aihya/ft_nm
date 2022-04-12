# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/28 16:28:57 by aihya             #+#    #+#              #
#    Updated: 2022/04/12 22:13:35 by aihya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = ft_nm

SRC_NAME =	elf.c \
			elf32.c \
			elf64.c \
			sort.c \
			show64.c \
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

all : $(NAME)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 
	@echo "Compiling \033[1;33m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) $(INCLUDE) -Llibft -lft -o $@ -c $<

libft_all:
	@make -C libft

$(NAME): libft_all $(OBJ)
	@echo "\033[1;33mCreating $(NAME)\033[0m"
	@gcc $(OBJ) -Llibft -lft  -o $@

clean :
	@make -C libft clean
	@echo "\033[1;33mRemoving $(NAME)'s objects directory\033[0m"
	@/bin/rm -rf $(OBJ_PATH) 2> /dev/null

fclean : clean
	@make -C libft fclean
	@echo "\033[1;33mRemoving $(NAME)\033[0m"
	@/bin/rm -f $(NAME)

re : fclean all