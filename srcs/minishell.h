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
int     minishell(c_table *ctable);
int	init_struct(c_table *);

/*utils*/
int	get_next_line(int fd, char **line);

/*lexer_utils*/
int		ft_isin(int c, char *set);
int		skip_spaces(char *line);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int n);
size_t	ft_strlen(const char *s);
int		ft_isalpha(int c);
int		ft_isprint(int c);
void	ft_strdel(char **s);
int		skip_quote(char *line, char quote, int i);

/*lexer_tokens*/
char	*quote_token(char *line);
char	*redirec_token(char *line);
char	*semic_token(char *line);
char	*pipe_token(char *line);
char	*word_token(char *line);
char	*dollar_token(char *line);

#endif
