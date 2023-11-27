# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 15:22:23 by btan              #+#    #+#              #
#    Updated: 2023/11/27 11:13:58 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME):
	make -C Libft
	mv ./Libft/libft.a ./
	make fclean -C Libft
	$(CC) $(SRC) -o pipex -I. -ILibft libft.a -g

#.c.o:
	#$(CC) $< -o $(<:.c=.o) -o pipex -I. -l$(NAME) -ILibft libft.a -g

#$(NAME): $(OBJECTS)
#	ar -rc $(NAME) $(OBJECTS)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

test-make:
	make -C Libft
	mv ./Libft/libft.a ./
	make fclean -C Libft
test: test-make
	$(CC) tests/main.c -o pipex -L -l $(NAME) -ILibft libft.a -g
run:
	clear && ./a.out
tester:
	$(CC) tests/test_pipe.c -L -l $(NAME) -o tester && ./tester && rm tester
.PHONY: all clean fclean re
