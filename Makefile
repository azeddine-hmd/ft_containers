NAME = container
COMPILER = c++
SRC = test/main.cpp
FLAGS_DEBUG = --std=c++98 -Wall -Wextra -Werror  -g3 -fsanitize=address
FLAGS = --std=c++98 -Wall -Wextra -Werror

all: std

std: $(SRC)
	@$(COMPILER) $(FLAGS_DEBUG) $(SRC) -D STD=1 -o $(NAME)

ft: $(SRC)
	@$(COMPILER) $(FLAGS_DEBUG) $(SRC) -o $(NAME)

first: vector map stack

second: second_vector second_map second_stack

vector:
	@$(COMPILER) $(FLAGS)	tests/Vector_tests.cpp -o vector.out

map:
	@$(COMPILER) $(FLAGS)	tests/Map_tests.cpp -o map.out

stack:
	@$(COMPILER) $(FLAGS)	tests/Stack_tests.cpp -o stack.out

second_vector:
	@$(COMPILER) $(FLAGS) tests/vector_test.cpp -o vector.out

second_stack:
	@$(COMPILER) $(FLAGS) tests/stack_test.cpp -o stack.out

second_map:
	@$(COMPILER) $(FLAGS) tests/map_test.cpp -o map.out

clean:
	@rm -f vector.out map.out stack.out set.out container
