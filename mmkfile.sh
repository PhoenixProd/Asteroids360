#!/bin/bash
echo -e -n "##
## EPITECH PROJECT, 2019
## $(get_highest_level $PWD)
## File description:
## Makefile
##

NAME = $1

FILES = " > "Makefile"
tree -i -f "." | cat | grep "\.cpp" | grep -v "bonus/"| sed -z "s/\n/ @£/g" | sed "s/ @£$//g" | tr "@" "\\" | sed -z "s/£/\n	/g" | sed "s/\.\///g" >> "Makefile"
echo -e "

FLAGS = $2

all :	\$(NAME)

\$(NAME):
	g++ -o \$(NAME) \$(FILES) \$(FLAGS)

clean:
	rm -f *.o
	rm -f *# *~ ./*/*# ./*/*~ ./*/*/*# ./*/*/*~ vgcore*

fclean:	clean
	rm -f \$(NAME)

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
	g++ -g3 -o \$(NAME) \$(FILES) -Wall -Wextra \$(FLAGS)

valgrind:
	clear
	g++ -g3 -o \$(NAME) \$(FILES) \$(FLAGS)

update:
	./mmkfile.sh $1 \"\$(FLAGS)\"" >> Makefile
echo "Makefile created"
