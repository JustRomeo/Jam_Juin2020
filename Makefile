##
## EPITECH PROJECT, 2019
## Jam 2020
## File description:
## Makefile
##

SRCP =	src/
DISP =	src/Display/
GAMP =	src/Game/
INTP =	src/Interface/
MAPP =	src/Map/
MENP = 	src/Menu/
PLAP =	src/Player/
PROJ = 	src/Projectile/
COMP =	src/SFMLComponents/
SYSP =	src/System/

SRC =	$(SRCP)main.cpp					\
		\
		$(COMP)EventHandler.cpp			\
		$(COMP)ImageSFML.cpp			\
		$(COMP)MusicSFML.cpp			\
		$(COMP)TextSFML.cpp				\
		$(DISP)Sprite.cpp				\
		$(DISP)Window.cpp				\
		$(GAMP)Ennemis.cpp				\
		$(GAMP)Objet.cpp				\
		$(GAMP)Projectile.cpp			\
		$(GAMP)GameLoop.cpp				\
		$(GAMP)Lootable.cpp				\
		$(GAMP)GameMusic.cpp			\
		$(INTP)Multiplayer.cpp			\
		$(INTP)Cinematique.cpp			\
		$(MAPP)Block.cpp				\
		$(MAPP)Door.cpp					\
		$(MAPP)Mapper.cpp				\
		$(MAPP)MapUpdater.cpp			\
		$(MENP)BugsScreen.cpp			\
		$(MENP)Death.cpp				\
		$(MENP)Echap.cpp				\
		$(MENP)Button.cpp 				\
		$(MENP)MainMenu.cpp				\
		$(MENP)MapMenu.cpp				\
		$(PLAP)Battery.cpp				\
		$(PLAP)Character.cpp			\
		$(PLAP)HUD.cpp					\
		$(PLAP)MunPlus.cpp				\
		$(PLAP)Time.cpp 				\
		$(PROJ)OrangeProjectile.cpp 	\
		$(PROJ)BlueProjectile.cpp 		\
		$(PROJ)PurpleProjectile.cpp 	\
		$(PROJ)GreenProjectile.cpp 		\
		$(PROJ)ProjectileFactory.cpp 	\
		$(SYSP)Connection.cpp			\
		$(SYSP)ErrorHandling.cpp		\
		$(SYSP)Exception.cpp			\
		$(SYSP)Paths.cpp				\
		$(SYSP)System.cpp				\

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
			-I./Class/Interface			\
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