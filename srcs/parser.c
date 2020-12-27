#include "minishell.h"

int			is_redirec(char *token)
{
	return (ft_strcmp(token, ">>") == 0 || ft_strcmp(token, ">") == 0 
	|| ft_strcmp(token, "<") == 0);
}

int			is_flag(char *token)
{
	return (token[0] == '-');
}

int			is_pipe(char *token, c_table *ctable)
{
	if (ft_strcmp(token, "|") == 0)
		return ((ctable->pipeout = 1));
	return (0);
}

int			is_quote(char c)
{
	if (c == 96 || c == 39 || c == 34)
		return (c);
	return (0);
}

char		*is_subshell(char *token)
{
	char	*str;

	str = malloc(2);
	if (is_quote(token[0]))
	{
		str[1] = 0;
		str[0] = token[0];
		return (str);
	}
	return (NULL);
}

int			separator(char *token)
{
	if (ft_strcmp(token, ";") == 0)
		return (COMMA);
	else if (ft_strncmp(token, "&&", 2) == 0)
		return (AMPERSAND);
	return (0);
}

int			redirection(c_table *ctable, char **token)
{
	char	*redirec;
	char	*file;

	redirec = *token;
	file = *(++token);
	if (ft_strncmp(redirec, ">>", 2) == 0 && (ctable->out |= APPEND))
	{
		ctable->fileout = ft_strdup(file);
	}
	else if (ft_strcmp(redirec, ">") == 0 && (ctable->out |= TRUNC))
	{
		ctable->fileout = ft_strdup(file);
	}
	else if (ft_strcmp(redirec, "<") == 0 && (ctable->in |= READ))
	{
		ctable->filein = ft_strdup(file);
	}
	return (0);
}

int			parser(c_table *ctable, char **tokens)
{
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "exit") == 0) 
			exit(*((int*)getglobal(STATUS)));	
		else if (ctable->command_exists == 0)
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
		else if (is_redirec(*tokens) != 0)
		{
			redirection(ctable, tokens++);
		}
		else if (ctable->command_exists == 1)
		{
			ctable->args = expanse_array(ctable->args, ctable->args_len, *tokens);
			ctable->args_len++;
		//	ctable->args = ft_strjoin(ctable->args , *tokens);
		}
		tokens++;
	}
	return (0);	
}
