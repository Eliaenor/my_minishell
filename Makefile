# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/23 03:57:06 by vcourtin          #+#    #+#              #
#    Updated: 2014/01/27 18:32:17 by vcourtin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell3

SRC_C = changedir.c check.c env1.c env2.c choice.c functions.c lib.c \
		main.c test.c term.c signal.c arrow.c delete_buff.c edit_tab.c \
		key.c get_line.c ctrl.c

LIB_A = libft.a

FLAG = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@cd libft; make re
	gcc -ltermcap -o $(NAME) $(FLAG) $(SRC_C) $(LIB_A)

gdb:
	@cd libft; make re
	gcc -g -ltermcap -o $(NAME) $(FLAG) $(SRC_C) $(LIB_A)

reload: re
	./$(NAME)

test: fclean gdb
	./$(NAME) 2>> TEST

clean:
	@cd libft; make clean
	@/bin/rm -f $(LIB_A)
	@rm -rf $(NAME).dSYM

fclean: clean
	@cd libft; make fclean
	@/bin/rm -f $(NAME)

re: fclean all
