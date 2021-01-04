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

/*global variable*/

t_list	*g_env;
void	*getglobal(int mode);
void	exitroutine();

/*PROCESS*/
int	id;

/*minishell modules*/
int	minishell();
char	**lexer(char *input_line);
int	subshell(char *);
int	parser(c_table *, char **);
void	executor(c_table *);
void	args(char **argv);
int	print(char *s, int fd);
int	echo(char *arg, char *flags, int in, int out);

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

/*Struct Utils*/
int	init_struct(c_table **);
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
char	*quote_token(char *line);
char	*redirec_token(char *line);
char	*semic_token(char *line);
char	*pipe_token(char *line);
char	*word_token(char *line);
char	*dollar_token(char *line);

/*env*/
//<<<<<<< HEAD
//int	env_builtin(int out);
//=======
int		env_builtin(char *cmd, int out);
//>>>>>>> e55579ef6298c3aa732374a42741ddeba7790c77
t_list	*setEnv(char **envp);
int		add_pwd();
int		add_shlvl();
int		add_underscore(char *cmd);

///*export*/
//<<<<<<< HEAD
//int	export_builtin(char *arg, int out);
//char	*find_node(t_list **lst, char *data);
//int	join_sorted_list(t_list *env_lst, int out);
//=======
int		export_builtin(char *arg, int out);
int		export_builtin_loop(char **arg, int out);
char	*find_node(char *data);
int		join_sorted_list(t_list *env_lst, int out);
//>>>>>>> e55579ef6298c3aa732374a42741ddeba7790c77

/*pwd*/
int	pwd_builtin(int out);

/*unset*/
int	unset_builtin(char *arg, char *exportarg);
int unset_builtin_loop(char **arg, char *exportarg);

/*absolute path*/
char	*absolute_path(char *cmd);
int	fork_cmd(char *cmd);

/*dollar*/
char	*dollar_swap(char *tokens);
char	*interrodollar_swap(char *itoa_id, char *cmd);

#endif
