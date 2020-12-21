CC = gcc
SRCDIR = ./srcs/*.c
UTILDIR = ./srcs/utils/*.c
FLAGS = -g -Wall -Wextra -Werror $(SRCDIR) $(UTILDIR)
DEPS = srcs/minishell.h #not needed

all: 
	$(CC) $(FLAGS) 
