all: myshell

myshell: myshell.c
	gcc -Wall -Wextra -g myshell.c -o myshell

clean:
	rm -f myshell
