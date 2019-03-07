CC = g++

RM = rm -f

CPPFLAGS = -W -Wall -Werror -Wextra -std=c++14 -fpic

LDFLAGS = -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lGLU -lGL -lXext -ldl

NAME = lib_arcade_opengl.so

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
