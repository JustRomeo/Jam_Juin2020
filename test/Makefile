##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

NAME		=	lib_arcade_sfml

NAME_EXEC 	= 	sfml

SRC			=	main.cpp					\
				src/Exception.cpp			\
				src/Sprite.cpp				\
				src/Sfml.cpp				\

SRC_LIB		=	main.cpp					\

OBJSHARED	=	main.o 						\
				Exception.o					\
				Sprite.o					\
				Sfml.o						\

OBJ			=	$(SRC:.cpp=.o)

CC			= 	g++

SFML 		=	-lsfml-system	\
				-lsfml-window	\
				-lsfml-graphics	\
				-lsfml-audio	\

CPPFLAGS	=	-I./class -I./../../class/ $(SFML)

CRITERION 	= 	--coverage -lcriterion

all			:	$(NAME)

$(NAME)		:	$(OBJ)
				#$(CC) $(SRC_LIB) $(SRC) -o $(NAME_EXEC) $(CPPFLAGS)
				$(CC) -o $(NAME_EXEC) $(SRC) $(CPPFLAGS)

clean		:
				rm -fr $(OBJ)
				rm -fr $(OBJSHARED)

fclean		:	clean
				rm -rf $(NAME)
				rm -rf $(NAME_EXEC)
				rm -rf ../$(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
