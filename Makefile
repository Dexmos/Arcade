CC = g++

RM = rm -f

CPPFLAGS = -W -Wall -Wextra -Werror -std=c++14

LDFLAGS = -ldl

NAME = arcade

SRCS =	core/main.cpp \
		core/CoreProgram.cpp \
		core/Score.cpp

LIB_SFML = lib/SFML
LIB_OPENGL = lib/OPENGL

LIB_SNAKE = games/snake

LIB_SOLARFOX = games/Solarfox

LIB_CACA = lib/lib_caca

OBJS = $(SRCS:.cpp=.o)

all:
	make -C $(LIB_SNAKE)
	make -C $(LIB_SOLARFOX)
	make $(NAME)

graphic:
	make -C $(LIB_SFML)
	make -C $(LIB_CACA)
	make -C $(LIB_OPENGL)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	make clean -C $(LIB_SFML)
	make clean -C $(LIB_SNAKE)
	make clean -C $(LIB_SOLARFOX)
	make clean -C $(LIB_OPENGL)
	make clean -C $(LIB_CACA)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIB_SFML)
	make fclean -C $(LIB_SNAKE)
	make fclean -C $(LIB_SOLARFOX)
	make fclean -C $(LIB_OPENGL)
	make fclean -C $(LIB_CACA)
	$(RM) $(NAME)

re: fclean all graphic

.PHONY: all clean fclean re
