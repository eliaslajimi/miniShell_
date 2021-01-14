#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
#  define AMPERSAND 1	
#  define COMMA 2	
#  define READ 0
#  define TRUNC 01000
#  define APPEND 02000
#  define STRUCT 1
#  define STATUS 2
# endif

/*command table*/

typedef struct	s_hwqd
{
		int		i;
		int		len;
		char	*result;
		int		*status;
		char	*str_status;
}				t_hwqd;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		t_table
{
	int				separator;
	int				pipein;
	int				pipeout;
	char			*command;
	char			*flags;
	char			**args;
	int				args_len;
	int				in;
	int				out;
	char			*filein;
	char			*fileout;
	struct t_table	*next;
	t_list			*env;
	int				command_exists;
}					c_table;

c_table *init, *ctable;
/*global variable*/

t_list	*g_env;
void	*getglobal(int mode);
void	exitroutine();

/*PROCESS*/
int	id;

/*minishell modules*/
int	minishell();
void	wrapper(c_table *ctable);
char	**lexer(char *input_line);
int	subshell(char *);
int	parser(c_table *, char **);
void	executor(c_table *);
void	args(char **argv);
int	print(char *s, int fd);
int	echo(char **arg, int in, int out);
int cd(char **arg, int in, int out);

/*utils*/
int	get_next_line(int fd, char **line);
int	ft_strcmp(const char *, const char *);
int	ft_strncmp(const char *, const char *, size_t );
int	ft_strlen(const char *s);
char	**ft_split(char *, char);
char	*ft_strtrim(char const *, char const *);
char	*ft_substr(char *, int , int );
char	*ft_strndup(const char *s1, int n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_char(char *s1, char c);
char	*ft_strdup(char *s1);
void	*ft_calloc(int count, int size);
void	ft_free_array(char **tab);
int	ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	*ft_memcpy(void *dst, const void *src, size_t n);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
char	**expanse_array(char **array, int previous_size, char *new_token);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_strcpy(char *dst, char *src, int n);
char	*ft_itoa(int n);
int		ft_atoi_minishell(const char *s);
char	*ft_strchr(const char *s, int c);
char	*remove_char(char *str, char c);
char	*remove_char_pos(char *str, int c);
char	*remove_all_char(char *str, char c);
int		ft_isdigit(int c);

/*Struct Utils*/
c_table *init_struct();
void	add_struct(c_table **ctable);
void	next_struct(c_table **ctable);
void	print_struct(c_table *ctable);
void	free_struct(c_table *ctable);

/*lexer_utils*/
int	ft_isin(int c, char *set);
int	skip_spaces(char *line);
int	ft_isprint(int c);
void	ft_strdel(char **s);
char	*matching_quotes(char *);
int		skip_quote(char *line, char quote, int i);
char	*quote_token(char *line);
char	*redirec_token(char *line);
char	*semic_token(char *line);
char	*pipe_token(char *line);
char	*word_token(char *line);
int		word_token_len(char *line);
char	*dollar_token(char *line);
char	*handling_word_quotes_dollar(char *word);

/*parser utils*/
char		*hdoublequotes(char *word);
char	*handle_double_quote(char *token);
char	*handle_simple_quote(char *token);
char	*swap_dollar(char *s, int i, int len);

/*env*/
int		env_builtin(char **args, int out);
t_list	*setEnv(char **envp);
int		add_pwd();
int		add_shlvl();
int		add_underscore(char *cmd);

///*export*/
int		export_builtin(char *arg, int out);
int		export_builtin_loop(char **arg, int out);
char	*find_node(char *data);
char *cleannode(char *node);
int		join_sorted_list(t_list *env_lst, int out);

/*pwd*/
int	pwd_builtin(char **args, int out);

/*unset*/
int	unset_builtin(char *arg, char *exportarg);
int unset_builtin_loop(char **arg, char *exportarg);

/*exit*/
void	exit_builtin(char **args);

/*absolute path*/
char	*absolute_path(char *cmd);
int	fork_cmd(char *cmd, char **args);

/*dollar*/
char	*dollar_swap(char *tokens);
char	*interrodollar_swap(char *itoa_id, char *cmd);

#endif
