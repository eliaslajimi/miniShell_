/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:52:56 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/10 11:34:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
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

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_pars
{
	int				i;
	int				*status;
	int				result;
}					t_pars;

typedef struct		s_wt
{
	int				i;
	int				start;
	char			quote_type;
	char			*token;
}					t_wt;

typedef struct		s_iaj
{
	int				i;
	int				j;
	int				n;
	t_list			*iter;
	char			*tmp;
	char			*declarex_lst;
}					t_iaj;

typedef struct		s_exp
{
	int				i;
	int				j;
	int				k;
	char			**split_arg;
	t_list			*env_lst;
	t_list			*newnode;
	char			*found;
}					t_exp;

typedef struct		s_mini
{
	int				i;
	char			**cmd;
	int				nb_cmd;
	char			*inputcmd;
	char			**tokens;
}					t_mini;

typedef struct		s_lex
{
	int				i;
	int				i_word;
	int				array_size;
	char			*token;
	char			**isolated_tokens;
}					t_lex;

typedef struct		s_arg
{
	int				start;
	int				end;
	char			*inputcmd;
	char			*cmd;
	char			**tokens;
}					t_arg;

typedef struct		s_hwqd
{
	int				i;
	int				len;
	char			*result;
	int				*status;
	char			*str_status;
}					t_hwqd;

typedef struct		s_table
{
	int				separator;
	int				pipein;
	int				pipeout;
	pid_t			id;
	char			*command;
	char			*flags;
	char			**args;
	int				args_len;
	int				in;
	int				out;
	char			*filein;
	char			*fileout;
	struct s_table	*next;
	t_list			*env;
	int				command_exists;
}					t_table;

t_list				*g_env;
void				*getglobal(int mode);
void				exitroutine(t_table *ctable);
int					minishell(t_mini);
void				wrapper(t_table *ctable);
char				**lexer(char *input_line);
int					subshell(char *str);
int					parser(t_table *ct, char **tab);
void				executor(t_table **ct);
void				args(char **argv);
int					print(char *s, int fd);
int					echo(char **arg, int args_len, int in, int out);
int					cd(char **arg, int in, int out);
t_mini				init_mini(t_mini *);
char				*get_inputcmd(void);
int					checking_pipes(char *inputcmd);
int					checking_semic(char *inputcmd);
int					skip_quote_lexer(char *line, char quote);
int					matching_quotes_args(char *line);
int					check_r_single(char **tokens, int i);
int					args_checker(char *inputcmd);
int					get_next_line(int fd, char **line);
int					ft_strcmp(const char *s, const char *str);
int					ft_strncmp(const char *str, const char *s, size_t i);
int					ft_strlen(const char *s);
char				**ft_split(char *str, char c);
char				*ft_strtrim(char const *s, char const *str);
char				*ft_substr(char *str, int i, int j);
char				*ft_strndup(const char *s1, int n);
char				*ft_strjoin(char *s1, char *s2);
char				**ft_strjoin2(char **s1, char **s2);
char				**appendtoptr(char **s1, char *s2);
char				*ft_strjoin_char(char *s1, char c);
char				*ft_strdup(char *s1);
void				*ft_calloc(int count, int size);
void				ft_free_array(char **tab);
int					ft_lstsize(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				*ft_memcpy(void *dst, const void *src, size_t n);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);
char				**expanse_array(char **array, int p_size, char *token);
char				*ft_strnstr(const char *h, const char *n, size_t len);
void				ft_strcpy(char *dst, char *src, int n);
char				*ft_itoa(int n);
int					ft_atoi_minishell(const char *s);
char				*ft_strchr(const char *s, int c);
char				*remove_char(char *str, char c);
char				*remove_char_pos(char *str, int c);
char				*remove_all_char(char *str, char c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					find_semic(char *line, int start);
int					ptr_len(void **ptr);
int					ft_isalpha(int c);
int					ft_atoi_shlvl(const char *str);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_lstfree(t_list	*head);
void				final_exit(int status);
char				**ft_split_cmd(char *s, int *nbr_cmd);
int					p(char *s1, char *s2, char *s3);
void				add_struct(t_table **ctable);
void				next_struct(t_table **ctable);
void				print_struct(t_table *ctable);
void				free_struct(t_table *ctable);
t_table				*init_struct(void);
t_table				**getstruct(void);
int					ft_isin(int c, char *set);
int					skip_spaces(char *line);
int					ft_isprint(int c);
void				ft_strdel(char **s);
char				*matching_quotes(char *str);
int					skip_quote(char *line, char quote, int i);
char				*quote_token(char *line);
char				*redirec_token(char *line);
char				*semic_token(char *line);
char				*pipe_token(char *line);
char				*word_token(char *line);
int					word_token_len(char *line);
char				*dollar_token(char *line);
char				*handling_word_quotes_dollar(char *word);
int					lexer_check(char *inputline);
int					lexer_special(char *input_line);
char				*check_token(char *line);
t_mini				init_mini_args(char *line);
void				handling_word_quotes_dollar2(t_hwqd *v, char *word);
void				single_quote(t_hwqd *v, char *word);
void				dollar2(t_hwqd *v, char *word);
void				dollar(t_hwqd *v, char *word);
void				double_quote2(t_hwqd *v, char *word);
void				double_quote(t_hwqd *v, char *word);
char				*hdoublequotes(char *word);
char				*handle_double_quote(char *token);
char				*handle_simple_quote(char *token);
char				*swap_dollar(char *s, int i, int len, int quotes);
int					is_redirec(char *token);
int					is_pipe(char *token, t_table *ctable);
int					is_quote(char c);
char				*is_subshell(char *token);
int					separator(char *token);
int					env_builtin(char **args, int out);
t_list				*set_env(char **envp);
int					add_pwd();
int					add_shlvl();
int					add_underscore(char *cmd);
int					add_underscore_main();
int					export_builtin(char *arg, int out);
int					export_builtin_loop(char **arg, int args_len, int out);
char				*find_node(char *data);
char				*cleannode(char *node);
int					join_sorted_list(t_list *env_lst, int out);
int					export_shlvl(char *nb);
int					pwd_builtin(char **args, int out);
int					unset_builtin(char *arg, char *exportarg);
int					unset_builtin_loop(char **arg, char *exportarg);
void				exit_builtin(char **args);
char				*absolute_path(char *cmd);
int					fork_cmd(char *cmd, char **args, t_table *ctable);
int					file_exists(const char *path);
char				*dollar_swap(char *tokens);
char				*interrodollar_swap(char *itoa_id, char *cmd);
char				*formatpath(char *path);
int					applycmd(char *cmd);
t_mini				prompt();
void				sighandler(int num);

#endif
