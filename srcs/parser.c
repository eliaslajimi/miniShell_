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

void			token_to_command(c_table *ctable, char **tokens, int **status)
{
		if (ft_strnstr(*tokens, "$?", 2))
			*tokens = interrodollar_swap(ft_itoa(**status), *tokens);		
		if (*tokens[0] == '\'')
			*tokens = handle_simple_quote(*tokens);
		if (*tokens[0] == '\"')
			*tokens = handle_double_quote(*tokens);
		if (*tokens[0] == '$')
			*tokens = dollar_swap(*tokens);
		if (ctable->command_exists == 0 && (ctable->command = *tokens))
			ctable->command_exists = 1;
		else if (is_flag(*tokens))
			ctable->flags = ft_strjoin(ctable->flags, *tokens);
		else if ((ctable->separator = separator(*tokens)) && (ctable->command_exists = 0))
			add_struct(&ctable);
		else if (is_pipe(*tokens, ctable) && (ctable->command_exists = 0)) 
			add_struct(&ctable);
		else if (is_redirec(*tokens) != 0)
			redirection(ctable, tokens++);
		else if ((ctable->command_exists == 1) && (ctable->args = expanse_array(ctable->args, ctable->args_len, *tokens)))
		{
			ctable->args_len++;
		}
			
}

int			parser(c_table *ctable, char **tokens)
{
	int		*status;

	status = (int*)getglobal(STATUS);
	while (*tokens)
	{
		token_to_command(ctable, tokens, &status);
		printf("token to command is %s\n", *tokens);
		tokens++;
	}
	return (0);	
}


