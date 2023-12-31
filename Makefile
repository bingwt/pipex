# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 15:22:23 by btan              #+#    #+#              #
#    Updated: 2023/12/19 14:30:11 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME):
	make -C Libft
	mv ./Libft/libft.a ./
	make fclean -C Libft
	$(CC) $(CFLAGS) -c $(SRCS) -I. -ILibft -g
	ar -rc $(NAME).a $(OBJECTS)
	$(CC) $(CFLAGS) main.c -o $(NAME) -I. -ILibft pipex.a libft.a -g

clean:
	rm -rf $(OBJECTS) $(NAME).a libft.a

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
