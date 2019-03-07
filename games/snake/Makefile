CC = g++

RM = rm -f

CPPFLAGS = -W -Wall -Werror -Wextra -std=c++14 -fpic

NAME = lib_arcade_snake.so

SRCS = Snake.cpp \
	../game/AGames.cpp \
		Apple.cpp \
		PlayProtocol.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) -shared $(OBJS)
	cp $(NAME) ../

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all
