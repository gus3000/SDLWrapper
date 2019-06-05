NAME = monprojet # à remplacer

CARGS = -W -Wall -Wextra
CC = g++
LIBS = -lSDL2 -lSDL2_image

SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=%.o)

DEPS = libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev cmake

COMPILE = $(CC) $(CARGS) $(LIBS)
NBFILES = $(words $(SRC))

SHELL := /bin/bash

restore = \e[0m
black   = \e[30m
red     = \e[31m
green   = \e[32m
yellow  = \e[33m
blue    = \e[34m
magenta = \e[35m
cyan    = \e[36m
white   = \e[37m

RESTORE = tput set
BLACK   = tput setaf 0
RED     = tput setaf 1
GREEN   = tput setaf 2
YELLOW  = tput setaf 3
BLUE    = tput setaf 4
MAGENTA = tput setaf 5
CYAN    = tput setaf 6
WHITE   = tput setaf 7

ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -c "COUNTTHIS")

N := x
C = $(words $N)$(eval N := x $N)
#ECHO = echo "`expr " [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"

ECHO = /bin/echo -e
ECHOF = /bin/echo -e "[$C/$(NBFILES)]"
endif

GETROW = IFS=';' read -sdR -p $$'\E[6n' ROW COL;echo "$${ROW\#*[}"
GETCOL = IFS=';' read -sdR -p $$'\E[6n' ROW COL;echo "$$COL"

default: $(NAME)

$(NAME): $(OBJ)
	@$(ECHO) "Linking $(cyan)$@$(restore)"
	@$(COMPILE) -o $@ $^ $(LIBS)

%.o: %.cpp
	@$(ECHOF) "Compiling $(green)$<$(restore)"
	@$(COMPILE) -c -o $@ $<

run: $(NAME)
	@printf '%*s' $$(tput cols) |tr " " "="
#	@echo $$($(GETROW)) $$($(GETCOL))
	@./$(NAME)

debug: $(NAME)
	@printf "=%.0s" {1..10}
	@valgrind ./$(NAME)

deps:
	@echo Installation de $(DEPS)...
	@sudo apt install $(DEPS)

clean:
	@echo "Cleaning..."
	@rm -f *.o $(NAME)
