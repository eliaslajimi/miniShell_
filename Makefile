CC = gcc
SRCDIR = ./srcs/*.c
UTILDIR = ./srcs/utils/*.c
TARGET = minishell
FLAGS = -o $(TARGET) -g -Wall -Wextra -Werror $(SRCDIR) $(UTILDIR)
DEPS = srcs/minishell.h #not needed

all: 
	$(CC) $(FLAGS)

leaks:
	$(CC) $(FLAGS) -g -fsanitize=address
