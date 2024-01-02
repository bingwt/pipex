# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 15:22:23 by btan              #+#    #+#              #
#    Updated: 2024/01/02 16:21:56 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c pipex_utils.c

BONUS_SRCS = pipex_bonus.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRCS:.c=.o)

BONUS_OBJECTS = $(BONUS_SRCS:.c=.o)

all: $(NAME) 

$(NAME):
	make -C Libft
	mv ./Libft/libft.a ./
	make fclean -C Libft
	$(CC) $(CFLAGS) -c $(SRCS) -I. -ILibft -g
	ar -rc $(NAME).a $(OBJECTS)
	$(CC) $(CFLAGS) main.c -o $(NAME) -I. -ILibft pipex.a libft.a -g

#bonus:
#	make -C Libft
#	mv ./Libft/libft.a ./
#	make fclean -C Libft
#	$(CC) $(CFLAGS) -c $(BONUS_SRCS) -I. -ILibft -g
#	ar rc $(NAME).a $(BONUS_OBJECTS)
#	$(CC) $(CFLAGS) main_bonus.c -o $(NAME) -I. -ILibft pipex.a libft.a -g
#
clean:
	rm -rf $(OBJECTS) $(BONUS_OBJECTS) $(NAME).a libft.a

fclean: clean
	rm -rf pipex

re: fclean all

test-pipex: re
	./pipex tests/infile cat ls tests/outfile
	cat tests/outfile
	rm tests/outfile

test-make:
	make -C Libft
	mv ./Libft/libft.a ./
	make fclean -C Libft

test: test-make
	$(CC) tests/main.c -o example -I. -ILibft libft.a -g

run:
	clear && ./a.out

tester:
	$(CC) tests/test_pipe.c -L -l $(NAME) -o tester && ./tester && rm tester

.PHONY: all clean fclean re
