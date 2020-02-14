##
## EPITECH PROJECT, 2019
## Asteroids360
## File description:
## Makefile
##

NAME = asteroids

FILES = src/bullet.cpp \
	src/core.cpp \
	src/main.cpp \
	src/vessel.cpp

FLAGS = -lsfml-graphics -lsfml-system -lsfml-window -lm -Isrc/include

all :	$(NAME)

$(NAME):
	g++ -o $(NAME) $(FILES) $(FLAGS)

clean:
	rm -f *.o
	rm -f *# *~ ./*/*# ./*/*~ ./*/*/*# ./*/*/*~ vgcore*

fclean:	clean
	rm -f $(NAME)

re:	fclean all

prepush:	fclean
	git add --all
	git status

tree:	prepush
	tree -a -I .git

push:	prepush
	git commit -m 'auto-sync with master'
	git push origin master

pull:
	git pull origin master

sync:	pull	push

debug:
	clear
	g++ -g3 -o $(NAME) $(FILES) -Wall -Wextra $(FLAGS)

valgrind:
	clear
	g++ -g3 -o $(NAME) $(FILES) $(FLAGS)

update:
	./mmkfile.sh asteroids "$(FLAGS)"
