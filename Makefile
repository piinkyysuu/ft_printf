# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thule <thule@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 08:46:18 by thule             #+#    #+#              #
#    Updated: 2022/04/20 14:39:17 by thule            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = 
NAME = libftprintf.a
FILES = ft_printf.c prototype.c printing_utils.c address_char_str.c number_utils.c signed_conversion.c unsigned_conversion.c float_conversion.c float_utils.c create_frac_part.c create_int_part.c
INCLUDE = ft_printf.h
LIB = libft/libft.a
OBJ = $(FILES:%.c=%.o)

.PHONY: clean fclean re
.SILENT: clean fclean re

all: test
	@./a.out

test: main.o $(NAME)
	@$(CC) -I $(INCLUDE) main.o $(NAME)

main.o: main.c
	@$(CC) -c $^ -o $@

$(NAME): $(OBJ) $(LIB)
	ar rc $@ $^
	ranlib $@

$(LIB): $(wildcard libft/*.o)
	$(MAKE) -sC ./libft
	cp $(LIB) $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

clean:
	$(MAKE) -sC ./libft clean
	/bin/rm -f $(OBJ)

fclean: clean
	$(MAKE) -sC ./libft fclean
	/bin/rm -f $(NAME)

re: fclean all
