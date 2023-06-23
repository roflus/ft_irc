NAME = ircserv
FLAGS = -Wall -Wextra -Werror -std=c++98
HEADER = -I ./include
SRC = 	./Src/main.cpp \
		./Src/server.cpp 
OBJ = $(SRC:%.cpp=%.o)

all: $(NAME)
$(NAME): $(OBJ)
	c++ $(OBJ) -o $(NAME)

%.o: %.cpp %.hpp
	c++ $(HEADER) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all