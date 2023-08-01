TARGET	:= ircserv
CC		:= c++
CFLAGS	:= -std=c++98 -Werror -Wall -Wextra

INC		:= -I include
SRC_DIR	:= src
OBJ_DIR	:= obj

SRCS	:= $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*.cpp)
OBJS	:= $(subst src, obj, $(SRCS:.cpp=.o))


all: dirs $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(INC) $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ $< -c $(INC) $(CFLAGS)

dirs:
	mkdir -p obj
	find src -type d -exec bash -c "echo '{}' | cut -c 5- | xargs -I {} mkdir -p obj/{}" \;

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re dirs
