# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 17:34:58 by lde-batz          #+#    #+#              #
#    Updated: 2019/03/08 11:44:29 by lde-batz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a 

SRC =	ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memccpy.c\
		ft_memmove.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strlen.c\
		ft_strdup.c\
		ft_strcpy.c\
		ft_strncpy.c\
		ft_strcat.c\
		ft_strncat.c\
		ft_strlcat.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strstr.c\
		ft_strnstr.c\
		ft_strcmp.c\
		ft_strncmp.c\
		ft_atoi.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_memalloc.c\
		ft_memdel.c\
		ft_strnew.c\
		ft_strdel.c\
		ft_strclr.c\
		ft_striter.c\
		ft_striteri.c\
		ft_strmap.c\
		ft_strmapi.c\
		ft_strequ.c\
		ft_strnequ.c\
		ft_strsub.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_strsplit.c\
		ft_itoa.c\
		ft_putchar.c\
		ft_putstr.c\
		ft_putendl.c\
		ft_putnbr.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_lstnew.c\
		ft_lstdelone.c\
		ft_lstdel.c\
		ft_lstadd.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_isspace.c\
		ft_putnbr_base.c\
		ft_sqrt.c\
		ft_factorial.c\
		ft_swap.c\
		get_next_line.c\
		ft_lstnewl.c\
		ft_next_sqrt.c\
		ft_atoi_base.c\
		ft_atof.c

SRC_DIR = srcs/

OBJ_DIR = objects/

OBJ := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

SRC := $(addprefix $(SRC_DIR), $(SRC))

HEADER = srcs

GCC = gcc -Wall -Wextra -Werror

.SILENT:

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME) $(OBJ)
	printf '\033[4m'
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Create Libft"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(GCC) -c -o $@ $< -I $(HEADER)
	printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Libft"

fclean: clean
	rm -rf $(NAME)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fclean Libft"

re: fclean all

$(OBJ_DIR):
	mkdir -p $@

.PHONY: all clean fclean re
