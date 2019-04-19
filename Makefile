# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cababou <cababou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/13 22:39:07 by cababou           #+#    #+#              #
#    Updated: 2019/04/19 17:00:09 by cababou          ###   ########.fr        #
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

NAME :=	doom

SRC := main.c doom.c quit.c read_map.c read_vertices.c read_sectors.c \
	raycasting.c fct.c event.c move.c mouse.c falling.c \
	game/draw.c ui/button/button.c editor/editor.c event_system_v2.c \
	ui/init_fonts.c ui/text/text.c ui/ui_ids.c ui/ui_el/ui.c \
	ui/text/text_util.c shapes/rect.c easter_eggs/hypercam.c \
	editor/base_events.c ui/button/button_util.c ui/button/button_events.c

OBJ := $(SRC:.c=.o)

PWD := $(shell pwd)
FRAMEWORKSDIR = ./

SRCDIR := srcs
OBJDIR := obj

SRCP :=		$(addprefix $(SRCDIR)/, $(SRC))
OBJP :=		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR :=	$(foreach dir, $(OBJP), $(shell dirname $(dir)))

LIB := -L libft/ -lft

INC := -I includes -I $(FRAMEWORKSDIR)/SDL2

FLAG := -g

FRAMEWORKSDIR := $(PWD)/frameworks
SDL := -F $(FRAMEWORKSDIR) -framework SDL2 -framework SDL2_ttf -Wl,-rpath $(FRAMEWORKSDIR)

TOTAL_FILES := $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find $(PWD)/obj/ -type f 2> /dev/null | wc -l | sed -e 's/ //g')

all : libft_comp $(NAME)

$(NAME) : $(OBJP)
			@gcc $(SDL) $(FLAG) $(OBJP) $(INC) $(LIB) -o $(NAME)
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Finished compilation. Output file : $(COL_VIOLET)$(PWD)/$(NAME)$(COL_END)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p $(ONLYDIR)
			@gcc -c $(FLAG) -F $(FRAMEWORKSDIR) $(INC) $< -o $@
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Compiling file [$(COL_VIOLET)$<$(COL_YELLOW)]. ($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"

libft_comp:
			@make -C libft

clean :
			@rm -rf $(OBJDIR)
			@make clean -C libft
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)compiled objects.$(COL_END)"

fclean :	clean
			@rm -rf $(NAME)
			@make fclean -C libft
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)$(NAME)$(COL_END)"

re :		fclean all
