##
## EPITECH PROJECT, 2019
## Jam 2020
## File description:
## Makefile
##

SRCP =		src/
CLAP =		Class/

SRC =		$(SRCP)main.cpp		\
			$(CLAP)Block.cpp	\
			$(CLAP)Mapper.cpp	\
			$(CLAP)System.cpp	\

OBJ =		$(SRC:.cpp=.o)

CC =		g++ -o

CRIT =		--coverage -lcriterion
WALL =		-Wall -Wextra -Werror
CRITERION =	unit_tests

NAME = soundwaves

CPPFLAGS +=	-I./include/	\
			-I./Class/		\

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

valgrind:	$(OBJCLI)
			$(CCO) $(NAME) -g3 $(OBJCLI) $(CPPFLAGS) $(WALL)
			$(RM) $(OBJCLI)
			valgrind ./$(NAME)

clean:
		$(RM) $(OBJ)

fclean:
		$(RM) $(OBJ)
		$(RM) $(NAME)

re:		fclean all