#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
#  define AMPERSAND 1	
#  define COMMA 2	
#  define OVERRIDE 2
#  define APPEND 3
# endif

/*command table*/
typedef struct		t_table
{
	int		separator;
	int		pipein;
	int		pipeout;
	char		*command;
	char		*flags;
	char		*args;
	int		in;
	int		out;
	char		*filein;
	char		*fileout;
	struct t_table	*next;	
}			c_table;

/*minishell modules*/
int     minishell();
char	**lexer(char *input_line);
int	subshell(char *);
int	parser(c_table *, char **);
int	executor(c_table *);

/*utils*/
int	get_next_line(int fd, char **line);
int	ft_strcmp(char *, char *);
int	ft_strncmp(const char *, const char *, size_t );
int	ft_strlen(const char *s);
char	**ft_split(char *, char);
char	*ft_strtrim(char const *, char const *);
char	*ft_substr(char *, int , int );
char	*ft_strndup(const char *s1, int n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);

int	init_struct(c_table **);
void	next_struct(c_table **ctable);
void	print_struct(c_table *ctable);

/*lexer_utils*/
int	ft_isin(int c, char *set);
int	skip_spaces(char *line);
//size_t	ft_strlen(const char *s);
//int	ft_isalpha(int c);
int	ft_isprint(int c);
void	ft_strdel(char **s);
//int	skip_quote(char *line, char quote, int i);

///*lexer_tokens*/
char	*quote_token(char *line);
char	*redirec_token(char *line);
char	*semic_token(char *line);
char	*pipe_token(char *line);
char	*word_token(char *line);
char	*dollar_token(char *line);

#endif
