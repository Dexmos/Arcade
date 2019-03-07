CC = g++

RM = rm -f

CPPFLAGS = -W -Wall -Werror -Wextra -std=c++14 -fpic

LDFLAGS = -lsfml-graphics -lsfml-system -lsfml-window

NAME = lib_arcade_sfml.so

SRCS = Graphics.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) -shared $(OBJS) $(LDFLAGS)
	cp $(NAME) ..

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all
