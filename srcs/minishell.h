#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
#  define AMPERSAND 1	/*separator*/
#  define COMMA 2	/*separator*/
# endif

/*command table*/
typedef struct		t_table
{
	int		echo;
	int		cd;
	int		pwd;
	int		exprt;
	int		unset;
	int		env;
	int		exit;
	int		separator;
	char		**flags;
	char		**args;
	struct t_table	*next;	
}			c_table;

/*init function to start new prompt*/
int     minishell();
int	init_struct(c_table *);

/*utils*/
int	get_next_line(int fd, char **line);

#endif
