##
## EPITECH PROJECT, 2019
## Jam 2020
## File description:
## Makefile
##

SRCP =	src/
DISP =	src/Display/
GAMP =	src/Game/
MAPP =	src/Map/
MENP = 	src/Menu/
PLAP =	src/Player/
COMP =	src/SFMLComponents/
SYSP =	src/System/
PROJ = 	src/Projectile/

SRC =	$(SRCP)main.cpp					\
		\
		$(COMP)ImageSFML.cpp			\
		$(COMP)MusicSFML.cpp			\
		$(DISP)Sprite.cpp				\
		$(DISP)Window.cpp				\
		$(GAMP)Ennemis.cpp				\
		$(GAMP)Projectile.cpp			\
		$(GAMP)GameLoop.cpp				\
		$(GAMP)GameMusic.cpp			\
		$(MAPP)Block.cpp				\
		$(MAPP)Door.cpp					\
		$(MENP)Death.cpp				\
		$(MENP)Echap.cpp				\
		$(MENP)MainMenu.cpp				\
		$(SYSP)Exception.cpp			\
		$(PLAP)Character.cpp			\
		$(PLAP)Time.cpp 				\
		$(PLAP)Battery.cpp				\
		$(PLAP)HUD.cpp					\
		$(PLAP)MunPlus.cpp				\
		$(MAPP)Mapper.cpp				\
		$(SYSP)System.cpp				\
		$(PROJ)OrangeProjectile.cpp 	\
		$(PROJ)BlueProjectile.cpp 		\
		$(PROJ)PurpleProjectile.cpp 	\
		$(PROJ)GreenProjectile.cpp 	\
		$(PROJ)ProjectileFactory.cpp 	\

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
			-I./Class/Display			\
			-I./Class/Game				\
			-I./Class/Map				\
			-I./Class/Menu				\
			-I./Class/Player			\
			-I./Class/SFMLComponents	\
			-I./Class/System			\
			-I./Class/Projectile		\
			$(SFML)

RM =	rm -rvf

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(NAME) $(OBJ) $(CPPFLAGS) $(WALL) -g3


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