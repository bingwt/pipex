# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 15:22:23 by btan              #+#    #+#              #
#    Updated: 2023/11/11 15:35:10 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

SRCS = 

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRCS:.c=.o)

all: $(NAME) 

.c.o:
	$(CC) -c $< -o $(<:.c=.o)

$(NAME): $(OBJECTS)
	ar -rc $(NAME) $(OBJECTS)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test:
	$(CC) tests/main.c -L -l $(NAME)
run:
	clear && ./a.out
tester:
	$(CC) tests/test_pipe.c -L -l $(NAME) -o tester && ./tester && rm tester
.PHONY: all clean fclean re
