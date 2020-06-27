##
## EPITECH PROJECT, 2019
## Jam 2020
## File description:
## Makefile
##

SRCP =	src/
CLAP =	src/class/
COMP =	src/class/SFMLComponents/

SRC =	$(COMP)ImageSFML.cpp	\
		$(CLAP)Block.cpp		\
		$(CLAP)Exception.cpp	\
		$(CLAP)GameLoop.cpp		\
		$(CLAP)Character.cpp	\
		$(CLAP)MainMenu.cpp		\
		$(CLAP)Mapper.cpp		\
		$(CLAP)Sprite.cpp		\
		$(CLAP)System.cpp		\
		$(CLAP)Window.cpp		\
		$(SRCP)main.cpp			\

OBJ =	$(SRC:.cpp=.o)

CC =	g++ -o

CRIT =	--coverage -lcriterion
WALL =	-Wall -Wextra -Werror
CRITERION =	unit_tests

NAME = soundwaves

SFML = 	-lsfml-system	\
		-lsfml-window	\
		-lsfml-graphics	\
		-lsfml-audio	\


CPPFLAGS =	-I./include/				\
			-I./Class/ 					\
			-I./Class/SFMLComponents	\
			-I./Class/Display			\
			-I./Class/Game				\
			-I./Class/Map				\
			-I./Class/Player			\
			-I./Class/SFMLComponents	\
			-I./Class/System			\
			$(SFML)

RM =	rm -rvf

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(NAME) $(OBJ) $(CPPFLAGS) $(WALL) -g3
			$(RM) $(OBJ)


tests_run:		$(OBJT)
				$(CCO) $(CRITERION) $(OBJT) $(CPPFLAGS) $(CRIT)
				./$(CRITERION)

clean_test:		$(SRCT)
				$(CCO) $(CRITERION) $(SRCT) $(CPPFLAGS) $(CRIT)
				./$(CRITERION)
				gcovr
				$(RM) *.o
				$(RM) *.gcno
				$(RM) *.gcda
				$(RM) $(CRITERION)

valgrind:	$(OBJ)
			$(CCO) $(NAME) -g3 $(OBJ) $(CPPFLAGS) $(WALL)
			$(RM) $(OBJ)
			valgrind ./$(NAME)

clean:
		$(RM) $(OBJ)

fclean:
		$(RM) $(OBJ)
		$(RM) $(NAME)

re:		fclean all