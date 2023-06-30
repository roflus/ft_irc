NAME = ircserv
FLAGS = -Wall -Wextra -Werror -std=c++98
HEADER = -I ./include
SRC = 	./Src/Main.cpp \
		./Src/Server/Server.cpp \
		./Src/Server/ServerClient.cpp \
		./Src/Client/Client.cpp \
		./Src/Channel/Channel.cpp \
		./Src/AllCommands/Commands.cpp \
		./Src/AllCommands/CheckCommands.cpp \
		./Src/AllCommands/Command/Invite.cpp \
		./Src/AllCommands/Command/Join.cpp \
		./Src/AllCommands/Command/Kick.cpp \
		./Src/AllCommands/Command/Mode.cpp \
		./Src/AllCommands/Command/Nick.cpp \
		./Src/AllCommands/Command/Pass.cpp \
		./Src/AllCommands/Command/Privmsg.cpp \
		./Src/AllCommands/Command/Quit.cpp \
		./Src/AllCommands/Command/Topic.cpp \
		./Src/AllCommands/Command/User.cpp 

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