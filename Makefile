#FILES = main.c
#	absolute_path.c \
#	args.c          \
#	args_checker.c  \
#	cd2.c           \
#	cd.c            \
#	dollar.c        \
#	echo.c          \
#	env2.c          \
#	env.c           \
#	executor.c      \
#	exit.c          \
#	export2.c       \
#	export.c        \
#	export_utils.c  \
#	find_node.c     \
#	fork_cmd.c      \
#	lexer.c         \
#	lexer_hwqd2.c   \
#	lexer_hwqd.c    \
#	lexer_quote_token.c \
#	lexer_special.c \
#	lexer_tokens2.c \
#	lexer_tokens.c	\
#	main.c		\
#	minishell.c	\
#	minishell_utils.c \
#	parser2.c	\
#	parser.c	\
#	print.c		\
#	pwd.c		\
#	skip_quote.c	\
#	struct_utils.c	\
#	swap_dollar.c	\
#	unset.c		
#	/utils/ft_atoi.c 	\
#	/utils/ft_calloc.c    	\
#	/utils/ft_free_array.c	\
#	/utils/ft_isalpha.c   	\
#	/utils/ft_isascii.c   	\
#	/utils/ft_isdigit.c   	\
#	/utils/ft_isin.c      	\
#	/utils/ft_isprint.c   	\
#	/utils/ft_itoa.c      	\
#	/utils/ft_lstadd_back.c \
#	/utils/ft_lstfree.c   	\
#	/utils/ft_lstlast.c   	\
#	/utils/ft_lstnew.c    	\
#	/utils/ft_lstsize.c   	\
#	/utils/ft_memcpy.c    	\
#	/utils/ft_putchar_fd.c	\
#	/utils/ft_putnbr_fd.c 	\
#	/utils/ft_putstr_fd.c 	\
#	/utils/ft_split.c     	\
#	/utils/ft_split_cmd.c 	\
#	/utils/ft_strchr.c    	\
#	/utils/ft_strcmp.c    	\
#	/utils/ft_strcpy.c    	\
#	/utils/ft_strdel.c    	\
#	/utils/ft_strdup.c    	\
#	/utils/ft_strjoin.c   	\
#	/utils/ft_strjoin_char.c \
#	/utils/ft_strlen.c    	\
#	/utils/ft_strnstr.c   	\
#	/utils/ft_strtrim.c   	\
#	/utils/ft_substr.c    	\
#	/utils/get_next_line.c	\
#	/utils/ptr_len.c      	\
#	/utils/remove_char.c  	\
#	/utils/skip_spaces.c  	
#SRC=$(addprefix srcs/, $(FILES))
#DIR= ./srcs
#CC = gcc
#FLAGS = -Wall -Wextra -Werror
#TARGET = minishell
#
#OBJ = $(SRCNAME:%c, %o)
#
#all: $(TARGET)
#$(TARGET): $(OBJ)
#	$(CC) $(FLAGS) -o $(TARGET) $(SRC)
#	$(clean)
#clean: rm -rf $(SRCNAME)
CC = gcc
SRCDIR = ./srcs/*.c
UTILDIR = ./srcs/utils/*.c
TARGET = minishell
FLAGS = -o $(TARGET) -g -Wall -Wextra -Werror $(SRCDIR) $(UTILDIR)
DEPS= srcs/minishell.h
all: 
	$(CC) $(FLAGS)
