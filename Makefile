NAME = easyfind

CC = c++

CFLAGS = -Wall -Werror -Wextra -std=c++98

SRC = main.cpp

OBJ = ${SRC:.cpp=.o}

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

debug: $(SRC)
	@$(CC) $(CFLAGS) -g $(SRC) -o debug

.PHONY: clean fclean re debug
