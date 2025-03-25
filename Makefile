##
## EPITECH PROJECT, 2025
## arkade
## File description:
## Makefile
##

CORE_SRC 			= 		Core/src/main.cpp 						\
							Core/src/Core.cpp 						\

NIBBLER_SRC 		=		Game/Nibbler/src/Nibbler.cpp			\

MINESWEEPER_SRC 	=		Game/Minesweeper/src/Minesweeper.cpp 	\

SFML_SRC 			=		Graphic/SFML/src/SFML.cpp 				\

NCURSES_SRC 		=		Graphic/NCurses/src/NCurses.cpp 		\

TEST_SRC 			=		\

CORE_OBJ 			= 		$(CORE_SRC:%.cpp=obj/%.o)

NIBBLER_OBJ 		=		$(NIBBLER_SRC:%.cpp=obj/%.o)

MINESWEEPER_OBJ 	= 		$(MINESWEEPER_SRC:%.cpp=obj/%.o)

SFML_OBJ 			=		$(SFML_SRC:%.cpp=obj/%.o)

NCURSES_OBJ 		=		$(NCURSES_SRC:%.cpp=obj/%.o)

CORE_NAME			=		arcade

NIBBLER_NAME 		= 		lib/arcade_nibbler.so

MINESWEEPER_NAME 	= 		lib/arcade_minesweeper.so

SFML_NAME 			=		lib/arcade_sfml.so

NCURSES_NAME 		=		lib/arcade_ncurses.so

CORE_FLAGS 			= 		-I ./							\
							-I Core/include 				\
							-I Core/include/interface 		\

NIBBLER_FLAGS 		= 		-I Game/Nibbler/include

MINESWEEPER_FLAGS 	=		-I Game/Minesweeper/include

SFML_FLAGS 			= 		-I Graphic/SFML/include

NCURSES_FLAGS 		= 		-I Graphic/NCurses/include

CPPFLAGS 			= 		-Werror -Wall -Wextra -Iinclude

LIB_FLAGS 			=		-shared

TEST_FLAGS 			= 		--coverage -lcriterion $(CPPFLAGS)

LIBSFML_FLAGS 		= 		-lsfml-graphics -lsfml-window -lsfml-system

LIBNCURSES_FLAGS 	= 		-lncurses

RED             =     \033[1;31m
GREEN           =     \033[1;32m
BLUE            =     \033[1;34m
NC              =     \033[0m

all:	core games graphicals

debug: CPPFLAGS += -g
debug: all

core: $(CORE_NAME)

games: $(NIBBLER_NAME) $(MINESWEEPER_NAME)

graphicals: $(NCURSES_NAME) $(SFML_NAME)

$(CORE_NAME): $(CORE_OBJ)
	@echo -e "$(BLUE)Linking Core...$(NC)"
	@g++ -o $(CORE_NAME) $(CORE_OBJ) $(CPPFLAGS) $(CORE_FLAGS)

$(NIBBLER_NAME): $(NIBBLER_OBJ)
	@echo -e "$(BLUE)Linking Nibbler...$(NC)"
	@g++ $(LIB_FLAGS) -o $(NIBBLER_NAME) $(NIBBLER_OBJ) $(NIBBLER_FLAGS)

$(MINESWEEPER_NAME): $(MINESWEEPER_OBJ)
	@echo -e "$(BLUE)Linking Mineswipper...$(NC)"
	@g++ $(LIB_FLAGS) -o $(MINESWEEPER_NAME) 		\
		 $(MINESWEEPER_OBJ) $(MINESWEEPER_FLAGS)

$(SFML_NAME): $(SFML_OBJ)
	@echo -e "$(BLUE)Linking SFML...$(NC)"
	@g++ $(LIB_FLAGS) -o $(SFML_NAME) $(SFML_OBJ) $(SFML_FLAGS) 	\
		 $(LIBSFML_FLAGS) $(CORE_FLAGS)

$(NCURSES_NAME): $(NCURSES_OBJ)
	@echo -e "$(BLUE)Linking NCurses...$(NC)"
	@g++ $(LIB_FLAGS) -o $(NCURSES_NAME) $(NCURSES_OBJ) 		\
		 $(NCURSES_FLAGS) $(CORE_FLAGS) $(LIBNCURSES_FLAGS)

obj/%.o: ./%.cpp
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	@g++ -fPIC -c -o $@ $< $(CPPFLAGS) $(CORE_FLAGS) $(NIBBLER_FLAGS) 		\
					 $(MINESWEEPER_FLAGS) $(SFML_FLAGS) $(NCURSES_FLAGS)

obj/test/%.o: ./%.cpp
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	@g++ -c -o $@ $< $(TEST_SRC) $(TEST_FLAGS) $(CPPFLAGS) -fPIC

unit_test:
	@echo -e "$(GREEN)Compiling units tests$<...$(NC)"
	@g++ -o unit_tests $(TEST_SRC) $(TEST_FLAGS)

tests_run: unit_test
	@echo -e "$(GREEN)Start units tests...$(NC)"
	@./unit_tests

clean:
	@rm -rf obj *.gcda *.gcno

fclean: clean
	@rm -f $(CORE_NAME) 		\
		   $(NIBBLER_NAME) 		\
		   $(MINESWEEPER_NAME)	\
		   $(SFML_NAME) 		\
		   $(NCURSES_NAME)		\
		   unit_tests 			\

re:	fclean all
