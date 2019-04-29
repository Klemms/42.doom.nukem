# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cababou <cababou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/13 22:39:07 by cababou           #+#    #+#              #
#    Updated: 2019/04/05 14:30:57 by cababou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLEAR_LINE	= \033[2K
BEGIN_LINE	= \033[A
COL_END		= \033[0m
COL_RED		= \033[1;31m
COL_GREEN	= \033[1;32m
COL_YELLOW	= \033[1;33m
COL_BLUE	= \033[1;34m
COL_VIOLET	= \033[1;35m
COL_CYAN	= \033[1;36m
COL_WHITE	= \033[1;37m

NAME :=	libft.a

SRC :=	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
		ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
		ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
		ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
		ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
		ft_striteri.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c \
		ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c \
		ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
		ft_strtrim.c ft_strjoin.c ft_tolower.c ft_toupper.c ft_lstnew.c \
		ft_lstdelone.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_strrev.c \
		ft_lstgetfirst.c ft_lstgetlast.c ft_lstdel.c ft_lstget.c \
		ft_strsubuntilchar.c ft_lstswap.c listcontainer_new.c \
		listcontainer_addelement.c listcontainer_addall.c \
		listcontainer_removeelement.c listcontainer_reindex.c \
		listcontainer_size.c listcontainer_fastsize.c \
		ft_lststrsplit.c ft_strsplitone.c ft_letter_to_int.c \
		ft_hex_to_int.c ft_pow.c ft_hex_to_color.c \
		ft_rgba_to_int.c ft_lstget_fromelement.c get_next_line.c \
		ft_mmalloc.c ft_ffree.c

OBJ := 	$(SRC:.c=.o)

PWD :=		$(shell pwd)

OBJDIR := 	obj

OBJP :=		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR :=	$(foreach dir, $(OBJP), $(shell dirname $(dir)))

FLAG := 	-Wall -Wextra -Werror

TOTAL_FILES := $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell ls $(PWD)/obj/ 2> /dev/null | wc -l | sed -e 's/ //g')

all : $(NAME)

$(NAME) : $(OBJP)
			@ar rc $(NAME) $(OBJP)
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Finished compilation. Output file : $(COL_VIOLET)$(PWD)/$(NAME)$(COL_END)"

$(OBJDIR)/%.o: %.c libft.h get_next_line.h
			@mkdir -p $(ONLYDIR)
			@gcc -g -c -Wall -Wextra -Werror $< -o $@
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Compiling file [$(COL_VIOLET)$<$(COL_YELLOW)]. ($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"

clean :
			@rm -rf $(OBJDIR)
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)compiled objects.$(COL_END)"

fclean :	clean
			@rm -rf $(NAME)
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)$(NAME)$(COL_END)"

re :		fclean all