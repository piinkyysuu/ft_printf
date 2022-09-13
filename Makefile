# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thle <thle@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 08:46:18 by thule             #+#    #+#              #
#    Updated: 2022/09/13 09:24:57 by thle             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

INCLUDES_DIR = ./includes/

FILES = ft_printf.c prototype.c address_char_str.c number_utils.c signed_conversion.c unsigned_conversion.c float_conversion.c float_utils.c create_frac_part.c create_int_part.c rounding.c utils.c float_utils_2.c
SRCS_DIR = ./srcs/
SRCS = $(addprefix $(SRC_DIR), $(FILES))

OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(FILES:%.c=%.o))

LIB_DIR = ./libft/
LIB = $(addprefix $(LIB_DIR), libft.a)
LIB_INCLUDE = ./libft/includes/

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@ar rc $@ $^
	@ranlib $@

$(LIB): $(wildcard libft/*.o)
	@$(MAKE) -sC ./libft
	@cp $(LIB) $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@

clean:
	@$(MAKE) -sC ./libft clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@$(MAKE) -sC ./libft fclean
	@/bin/rm -f $(NAME)

re: fclean all
