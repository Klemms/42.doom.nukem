# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cababou <cababou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/13 22:39:07 by cababou           #+#    #+#              #
#    Updated: 2019/05/06 10:03:48 by cababou          ###   ########.fr        #
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

SRC := doom.c easter_eggs/hypercam.c editor/base_events.c \
	editor/editor.c editor/system_files/list_files.c errors/errors.c \
	events/event_system.c events.c free_structs.c game/game.c \
	line.c map/texture_loading.c \
	mlx_context/inits.c editor/map/load_map.c \
	player.c shapes/rect.c ui/button/button.c ui/button/button_events.c \
	ui/button/button_util.c ui/init_fonts.c ui/text/text.c \
	ui/text/text_util.c ui/ui_el/ui.c ui/ui_ids.c editor/editor_util.c \
	editor/renderers/flat_top_render.c editor/switcher.c \
	animation/fade.c editor/ui_clicks/ui_clicks.c editor/tools.c \
	map/converter.c map/map_util.c move.c \
	editor/renderers/bottom_select_render.c lov/raycasting.c \
	editor/renderers/right_bar_render.c \
	ui/wjauge/wjauge.c \
	ui/checkbox/checkbox.c \
	editor/blocks.c \
	editor/blocks2.c \
	map/save.c \
	map/map_util2.c \
	map/minimap.c \
	map/saving/map_write.c \
	map/saving/texture_write.c \
	map/loading/map_load.c \
	map/loading/map_load2.c \
	map/loading/map_load3.c \
	map/loading/map_load4.c \
	map/expand.c

HEADERS := doom.h editor.h errors.h

OBJ := $(SRC:.c=.o)

PWD := $(shell pwd)
FRAMEWORKSDIR = ./

SRCDIR := src
OBJDIR := obj

HEADERSP := $(addprefix includes/, $(HEADERS))
SRCP :=		$(addprefix $(SRCDIR)/, $(SRC))
OBJP :=		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR :=	$(foreach dir, $(OBJP), $(shell dirname $(dir)))

LIB := -L libft/ -lft

INC := -I includes -I $(FRAMEWORKSDIR)/SDL2

FLAG := -g

FRAMEWORKSDIR := $(PWD)/frameworks
SDL := -F $(FRAMEWORKSDIR) -framework SDL2 -framework SDL2_ttf -framework SDL2_image -framework SDL2_mixer -Wl,-rpath $(FRAMEWORKSDIR)

TOTAL_FILES := $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find $(PWD)/obj/ -type f 2> /dev/null | wc -l | sed -e 's/ //g')

all : libft_comp $(NAME)

$(NAME) : $(OBJP)
			@gcc $(SDL) $(FLAG) $(OBJP) $(INC) $(LIB) -o $(NAME)
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Finished compilation. Output file : $(COL_VIOLET)$(PWD)/$(NAME)$(COL_END)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERSP) libft/libft.a
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
