# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/25 10:52:42 by lde-batz          #+#    #+#              #
#    Updated: 2019/03/15 12:44:14 by lde-batz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom

SRC = 	main.c\
		doom.c\
		quit.c\
		read_map.c\
		read_vertices.c\
		read_sectors.c\
		raycasting.c\
		fct.c\
		event.c\
		move.c\
		mouse.c\
		falling.c\
		cp_main.c

SRC_DIR = srcs/

OBJ_DIR = objects/

OBJ := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

SRC := $(addprefix $(SRC_DIR), $(SRC))

INC = -I includes

LIB = -L libft/ -lft

GCC = gcc -Wall -Wextra -Werror -o -o1 -o2 -o3

SDL_FLAG = -framework SDL2

.SILENT:

all: lib $(NAME)

$(NAME): $(OBJ)
	$(GCC) -o $(NAME) $(SRC) $(LIB) $(SDL_FLAG)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Create Wolf3D"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(GCC) -c $< -o $@ $(INC)
	printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

lib:
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJ)
	rm -Rf $(OBJ_DIR)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Wolf3D"

fclean: clean
	make -C libft fclean
	rm -f $(NAME)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fclean Wolf3D"

re: fclean all

.PHONY: all clean fclean re

