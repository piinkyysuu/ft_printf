# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thle <thle@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 08:46:18 by thule             #+#    #+#              #
#    Updated: 2022/04/12 12:13:40 by thle             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = 
NAME = libftprintf.a
FILES = ft_printf.c prototype.c printing_utils.c string_and_char.c number_utils.c signed_conversion.c unsigned_conversion.c
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
