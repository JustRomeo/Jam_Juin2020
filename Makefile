##
## EPITECH PROJECT, 2019
## Jam 2020
## File description:
## Makefile
##

SRCP =	src/
DISP =	src/Display/
CREP =	src/Creator/
GAMP =	src/Game/
INTP =	src/Interface/
LVLP =	src/Level/
MAPP =	src/Map/
MENP = 	src/Menu/
PLAP =	src/Player/
PROJ = 	src/Projectile/
COMP =	src/SFMLComponents/
SYSP =	src/System/

SRC =	$(SRCP)main.cpp					\
		\
		$(COMP)EventHandler.cpp			\
		$(COMP)InputControler.cpp		\
		$(COMP)ImageSFML.cpp			\
		$(COMP)LoadingBar.cpp			\
		$(COMP)ManetteSFML.cpp			\
		$(COMP)MusicSFML.cpp			\
		$(COMP)TextSFML.cpp				\
		$(COMP)WindowLib.cpp			\
		$(CREP)Map.cpp					\
		$(CREP)Training.cpp				\
		$(DISP)Sprite.cpp				\
		$(DISP)Window.cpp				\
		$(GAMP)Ennemis.cpp				\
		$(GAMP)GameLoop.cpp				\
		$(GAMP)Objet.cpp				\
		$(GAMP)Projectile.cpp			\
		$(GAMP)Runner.cpp				\
		$(GAMP)Lootable.cpp				\
		$(GAMP)GameMusic.cpp			\
		$(INTP)Multiplayer.cpp			\
		$(INTP)Cinematique.cpp			\
		$(MAPP)Block.cpp				\
		$(MAPP)Door.cpp					\
		$(MAPP)Mapper.cpp				\
		$(MAPP)MapUpdater.cpp			\
		$(MENP)BugsScreen.cpp			\
		$(MENP)ControlPanel.cpp			\
		$(MENP)Death.cpp				\
		$(MENP)Echap.cpp				\
		$(MENP)Button.cpp 				\
		$(MENP)MainMenu.cpp				\
		$(MENP)MapMenu.cpp				\
		$(PLAP)Battery.cpp				\
		$(PLAP)Character.cpp			\
		$(PLAP)CompetenceTree.cpp		\
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
CC3 =	g++ -g3 -o

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
			-I./Class/Creator			\
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
			$(CC) $(NAME) $(OBJ) $(CPPFLAGS) $(WALL)


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
			$(CC3) $(NAME) $(OBJ) $(CPPFLAGS) $(WALL)
			$(RM) $(OBJ)
			valgrind ./$(NAME)

clean:
		$(RM) $(OBJ)

fclean:
		$(RM) $(OBJ)
		$(RM) $(NAME)

re:		fclean all
