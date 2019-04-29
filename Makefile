# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cababou <cababou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/13 22:39:07 by cababou           #+#    #+#              #
#    Updated: 2019/04/05 14:44:24 by cababou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLEAR_LINE	:= \033[2K
BEGIN_LINE	:= \033[A
COL_END		:= \033[0m
COL_RED		:= \033[1;31m
COL_GREEN	:= \033[1;32m
COL_YELLOW	:= \033[1;33m
COL_BLUE	:= \033[1;34m
COL_VIOLET	:= \033[1;35m
COL_CYAN	:= \033[1;36m
COL_WHITE	:= \033[1;37m

NAME :=	wolf3d

SRC :=	wolf3d.c vectors.c parsing.c player.c lov/lov.c line.c init_sight.c \
		events.c draw.c errors/errors.c mlx_context/inits.c \
		map/texture_loading.c mlx_context/image_manip.c free_structs.c \
		lov/walls.c parsing_norme.c

OBJ := $(SRC:.c=.o)

PWD :=		$(shell pwd)
FRAMEWORKSDIR = /Library/Frameworks

SRCDIR := src
OBJDIR := obj

SRCP :=		$(addprefix $(SRCDIR)/, $(SRC))
OBJP :=		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR :=	$(foreach dir, $(OBJP), $(shell dirname $(dir)))

LIB := ./libft

FLAG := -Wall -Wextra -Werror -g

MLX := -lmlx -framework OpenGL -framework AppKit

TOTAL_FILES := $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell ls $(PWD)/obj/ 2> /dev/null | wc -l | sed -e 's/ //g')

all : mlx_comp libft_comp $(NAME)

$(NAME) : $(OBJP)
			@gcc $(FLAG) $(MLX) $(OBJP)  ./libft/libft.a -o $(NAME) -Lmlx_sierra -lmlx 
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Finished compilation. Output file : $(COL_VIOLET)$(PWD)/$(NAME)$(COL_END)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c  src/wolf3d.h libft/libft.a
			@mkdir -p $(ONLYDIR)
			@gcc -c $(FLAG) -I ./mlx_sierra/ $< -o $@
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Compiling file [$(COL_VIOLET)$<$(COL_YELLOW)]. ($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"

libft_comp:
			@make -C $(LIB)

mlx_comp:
			@make -C ./mlx_sierra

clean :
			@rm -rf $(OBJDIR)
			@make clean -C $(LIB)
			@make clean -C ./mlx_sierra
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)compiled objects.$(COL_END)"

fclean :	clean
			@rm -rf $(NAME)
			@make fclean -C $(LIB)
			@make clean -C ./mlx_sierra
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)$(NAME)$(COL_END)"

re :		fclean all
