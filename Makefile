##
## EPITECH PROJECT, 2019
## Asteroids360
## File description:
## Makefile
##

NAME = asteroids

FILES = 

FLAGS = -lsfml-system -lsfml-graphics

all :	$(NAME)

$(NAME):
	gcc -o $(NAME) $(FILES) $(FLAGS)

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
	gcc -g3 -o $(NAME) $(FILES) -Wall -Wextra $(FLAGS)

valgrind:
	clear
	gcc -g3 -o $(NAME) $(FILES) $(FLAGS)

update:
	mmkfile asteroids "-lsfml-system -lsfml-graphics"
