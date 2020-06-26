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

OBJ =		$(SRC:.cpp=.o)

CC =		g++ -o

CRIT =		--coverage -lcriterion
WALL =		-Wall -Wextra -Werror
CRITERION =	unit_tests

NAME = soundwaves

CFLAGS +=	-I./include/	\
			-I./Class/		\

RM =	rm -rvf

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(NAME) $(OBJ) $(CFLAGS) $(WALL) -g3
			$(RM) $(OBJ)


tests_run:		$(OBJT)
				$(CCO) $(CRITERION) $(OBJT) $(CFLAGS) $(CRIT)
				export LD_LIBRARY_PATH=$PWD/lib
				./$(CRITERION)

clean_test:		$(SRCT)
				$(CCO) $(CRITERION) $(SRCT) $(CFLAGS) $(CRIT)
				export LD_LIBRARY_PATH=$$PWD/lib
				./$(CRITERION)
				gcovr
				$(RM) *.o
				$(RM) *.gcno
				$(RM) *.gcda
				$(RM) $(CRITERION)

valgrind:	$(OBJCLI)
			$(CCO) $(CLINAME) -g3 $(OBJCLI) $(CFLAGS) $(WALL)
			$(RM) $(OBJCLI)
			export LD_LIBRARY_PATH=$$PWD/lib
			valgrind ./$(CLINAME) 127.0.0.1 9000

clean:
		$(RM) $(OBJ)

fclean:
		$(RM) $(OBJ)
		$(RM) $(NAME)

re:		fclean all