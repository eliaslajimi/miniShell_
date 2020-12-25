#include "minishell.h"

int	is_command(char *token)
{
	return (ft_strcmp(token, "echo") == 0 || ft_strcmp(token, "grep") == 0
	|| ft_strcmp(token, "cd") == 0|| ft_strcmp(token, "pwd") == 0
	|| ft_strcmp(token, "export") == 0 || ft_strcmp(token, "unset")
	|| ft_strcmp(token, "env") == 0 || ft_strcmp(token, "exit") == 0);
}

int	is_redirec(char *token)
{
	return (ft_strcmp(token, ">>") == 0 || ft_strcmp(token, ">") == 0 
	|| ft_strcmp(token, "<") == 0);
}

int	is_flag(char *token)
{
	return (token[0] == '-');
}

int	is_pipe(char *token, c_table *ctable)
{
	if (ft_strcmp(token, "|") == 0)
		return ((ctable->pipeout = 1));
	return (0);
}

int	is_quote(char c)
{
	if (c == 96 || c == 39 || c == 34)
		return (c);
	return (0);
}

char	*is_subshell(char *token)
{
	char *str;

	str = malloc(2);
	if (is_quote(token[0]))
	{
		str[1] = 0;
		str[0] = token[0];
		return (str);
	}
	return (NULL);
}

int	separator(char *token)
{
	if (ft_strcmp(token, ";") == 0)
		return (COMMA);
	else if (ft_strncmp(token, "&&", 2) == 0)
		return (AMPERSAND);
	return (0);
}

int	redirection(c_table *ctable, char **token)
{
	char *redirec;
	char *file;

	redirec = *token;
	file = *(++token);
	if (ft_strncmp(redirec, ">>", 2) == 0 && (ctable->out |= APPEND))
	{
		printf("R 1\n");
		ctable->fileout = ft_strdup(file);
	}
	else if (ft_strcmp(redirec, ">") == 0 && (ctable->out |= TRUNC))
	{
		printf("R 2\n");
		ctable->fileout = ft_strdup(file);
	}
	else if (ft_strcmp(redirec, "<") == 0 && (ctable->in |= READ))
	{
		printf("R 3\n");
		ctable->filein = ft_strdup(file);
	}
	else
		printf("R 4\n");
	return (0);
}

int	parser(c_table *ctable, char **tokens)
{
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "exit") == 0) 
			exit(0);	

		else if(ctable->command_exists == 0)
		{
			ctable->command = *tokens;
			ctable->command_exists = 1;
		}
		else if (is_flag(*tokens))
		{
			ctable->flags = ft_strjoin(ctable->flags, *tokens);
		}
		else if ((ctable->separator = separator(*tokens)))
		{
			add_struct(&ctable);
			ctable->command_exists = 0;
		}
		else if (is_pipe(*tokens, ctable))
		{
			add_struct(&ctable);
			ctable->command_exists = 0;
		}
//		else if (is_subshell(*tokens))//subshell is solely processes at lexer stage.
//			ctable->args = *tokens; 
		else if (is_redirec(*tokens) != 0)
		{
			redirection(ctable, tokens++);
		}
		else if (ctable->command_exists == 1)
		{
			ctable->args = ft_strjoin(ctable->args , *tokens);
		}
		tokens++;
	}
	return (0);	
}
