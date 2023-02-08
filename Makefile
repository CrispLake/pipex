# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 16:39:22 by emajuri           #+#    #+#              #
#    Updated: 2023/02/08 18:45:26 by emajuri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BONUS_NAME = pipex_bonus

LIBFT = libft.a

SRC = pipex.c split_quote.c get_path.c make_fd.c parent_n_child.c

OSRC = $(SRC:%.c=%.o)

BSRC = pipex_bonus.c split_quote.c get_path.c make_fd.c parent_n_child.c

BOSRC = $(BSRC:%.c=%.o)

WWW = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OSRC)
	make -C libft
	cc $(WWW) $(OSRC) -L libft -lft -o $(NAME)

clean:
	rm -f $(OSRC)
	rm -f $(BOSRC)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	rm -f libft/$(LIBFT)

%.o: %.c
	cc $(WWW) -c -o $@ $^ 

re: fclean all

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BOSRC)
	make -C libft
	cc $(WWW) $(BOSRC) -L libft -lft -o $(BONUS_NAME)
