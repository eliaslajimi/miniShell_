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

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

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
int	ft_isprint(int c);
void	ft_strdel(char **s);
char	*matching_quotes(char *line);

///*lexer_tokens*/
char	*quote_token(char *line);
char	*redirec_token(char *line);
char	*semic_token(char *line);
char	*pipe_token(char *line);
char	*word_token(char *line);
char	*dollar_token(char *line);

/*env*/
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		env_builtin(t_list *env_lst, int fd);
t_list	*get_env_var(char **envp);

/*pwd*/
void	pwd_builtin(t_list *env_list);

#endif
