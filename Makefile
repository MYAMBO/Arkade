##
## EPITECH PROJECT, 2025
## arkade
## File description:
## Makefile
##

CORE_SRC 			= 		Core/src/Lib.cpp 						\
							Core/src/Core.cpp 						\
							Core/src/main.cpp 						\
							Core/src/Menu.cpp 						\
							Core/src/Arkade.cpp 					\
							Core/src/Parsing.cpp 					\
							Core/src/MenuObject.cpp 				\

SNAKE_SRC 			=		Game/Snake/src/Snake.cpp				\
							Game/Snake/src/SnakeObject.cpp			\

MINESWEEPER_SRC 	=		Game/Minesweeper/src/Minesweeper.cpp 	\
							Game/Minesweeper/src/MineObject.cpp		\

SFML_SRC 			=		Graphic/SFML/src/SFML.cpp 				\

NCURSES_SRC 		=		Graphic/NCurses/src/NCurses.cpp 		\

SDL2_SRC 			=		Graphic/SDL2/src/SDL2.cpp 				\

TEST_SRC 			=		Core/src/Lib.cpp 						\
							Core/src/Core.cpp 						\
							tests/testCore.cpp 						\

CORE_OBJ 			= 		$(CORE_SRC:%.cpp=obj/%.o)

SNAKE_OBJ 			=		$(SNAKE_SRC:%.cpp=obj/%.o)

MINESWEEPER_OBJ 	= 		$(MINESWEEPER_SRC:%.cpp=obj/%.o)

SFML_OBJ 			=		$(SFML_SRC:%.cpp=obj/%.o)

NCURSES_OBJ 		=		$(NCURSES_SRC:%.cpp=obj/%.o)

SDL2_OBJ 			=		$(SDL2_SRC:%.cpp=obj/%.o)

CORE_NAME			=		arcade

SNAKE_NAME 			= 		lib/arcade_snake.so

MINESWEEPER_NAME 	= 		lib/arcade_minesweeper.so

SFML_NAME 			=		lib/arcade_sfml.so

NCURSES_NAME 		=		lib/arcade_ncurses.so

SDL2_NAME 			=		lib/arcade_sdl2.so

CORE_FLAGS 			= 		-I Core/include 				\
							-I Core/include/interface 		\

SNAKE_FLAGS 		= 		-I Game/Snake/include

MINESWEEPER_FLAGS 	=		-I Game/Minesweeper/include

SFML_FLAGS 			= 		-I Graphic/SFML/include

NCURSES_FLAGS 		= 		-I Graphic/NCurses/include

SDL2_FLAGS 			= 		-I Graphic/SDL2/include

CPPFLAGS 			= 		-Werror -Wall -Wextra -Iinclude

LIB_FLAGS 			=		-shared

TEST_FLAGS 			= 		--coverage -lcriterion $(CPPFLAGS)

LIBSFML_FLAGS 		= 		-lsfml-graphics -lsfml-window -lsfml-system

LIBNCURSES_FLAGS 	= 		-lncurses

LIBSDL2_FLAGS 		= 		-lSDL2 -lSDL2_image -lSDL2_ttf

RED             	=     \033[1;31m
GREEN          		=     \033[1;32m
BLUE          	  	=     \033[1;34m
NC              	=     \033[0m

all:	core graphicals games

debug: CPPFLAGS += -g
debug: all

core: $(CORE_NAME)

games: $(SNAKE_NAME) $(MINESWEEPER_NAME)

graphicals: $(NCURSES_NAME) $(SFML_NAME) $(SDL2_NAME)

$(CORE_NAME): $(CORE_OBJ)
	@echo -e "$(BLUE)Linking Core...$(NC)"
	@g++ -o $(CORE_NAME) $(CORE_OBJ) $(CPPFLAGS) $(CORE_FLAGS)

$(SNAKE_NAME): $(SNAKE_OBJ)
	@echo -e "$(BLUE)Linking SNAKE...$(NC)"
	@g++ $(LIB_FLAGS) -o $(SNAKE_NAME) $(SNAKE_OBJ) $(SNAKE_FLAGS)

$(MINESWEEPER_NAME): $(MINESWEEPER_OBJ)
	@echo -e "$(BLUE)Linking Mineswipper...$(NC)"
	@g++ $(LIB_FLAGS) -o $(MINESWEEPER_NAME) 								\
		 $(MINESWEEPER_OBJ) $(MINESWEEPER_FLAGS)

$(SFML_NAME): $(SFML_OBJ)
	@echo -e "$(BLUE)Linking SFML...$(NC)"
	@g++ $(LIB_FLAGS) -o $(SFML_NAME) $(SFML_OBJ) $(SFML_FLAGS) 			\
		 $(LIBSFML_FLAGS) $(CORE_FLAGS)

$(NCURSES_NAME): $(NCURSES_OBJ)
	@echo -e "$(BLUE)Linking NCurses...$(NC)"
	@g++ $(LIB_FLAGS) -o $(NCURSES_NAME) $(NCURSES_OBJ) 					\
		 $(NCURSES_FLAGS) $(CORE_FLAGS) $(LIBNCURSES_FLAGS)

$(SDL2_NAME): $(SDL2_OBJ)
	@echo -e "$(BLUE)Linking SDL2...$(NC)"
	@g++ $(LIB_FLAGS) -o $(SDL2_NAME) $(SDL2_OBJ) 					\
		 $(SDL2_FLAGS) $(CORE_FLAGS) $(LIBSDL2_FLAGS)

obj/%.o: ./%.cpp
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	@g++ -fPIC -c -o $@ $< $(CPPFLAGS) $(CORE_FLAGS) $(NIBBLER_FLAGS) 		\
					 $(MINESWEEPER_FLAGS) $(SNAKE_FLAGS) $(SFML_FLAGS) 		\
					 $(NCURSES_FLAGS) $(SDL2_FLAGS)

obj/test/%.o: ./%.cpp
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	@g++ -fPIC -c -o $@ $< $(TEST_SRC) $(TEST_FLAGS) $(CPPFLAGS)

unit_test: games graphicals
	@echo -e "$(GREEN)Compiling units tests...$(NC)"
	@g++ -o unit_tests $(TEST_SRC) $(TEST_FLAGS) $(CORE_FLAGS)

tests_run: unit_test
	@echo -e "$(GREEN)Start units tests...$(NC)"
	@./unit_tests

clean:
	@rm -rf obj *.gcda *.gcno

fclean: clean
	@rm -f $(CORE_NAME) 		\
		   $(SNAKE_NAME) 		\
		   $(MINESWEEPER_NAME)	\
		   $(SFML_NAME) 		\
		   $(NCURSES_NAME)		\
		   $(SDL2_NAME)		\
		   unit_tests 			\

re:	fclean all
