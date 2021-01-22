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
	if (!ft_strlen(file) || ft_isin(file[0], "|><"))
	{
		print("wrong file", 1);
		return (-1);
	}
	if (ft_strncmp(redirec, ">>", 2) == 0 )
    {
        ctable->fileout = ft_strdup(file);
        if (ft_strcmp(ctable->fileout, "") != 0)
        {
            ctable->out  = open(ctable->fileout, O_CREAT | O_RDWR | O_APPEND, 777);
        }
    }
    else if (ft_strcmp(redirec, ">") == 0 )
    {
        ctable->fileout = ft_strdup(file);
        if (ft_strcmp(ctable->fileout, "") != 0)
        {
            ctable->out  = open(ctable->fileout, O_CREAT | O_RDWR | O_TRUNC , 777);
        }
    }
	else if (ft_strcmp(redirec, "<") == 0 )
	{
		ctable->filein = ft_strdup(file);
		if (ft_strcmp(ctable->filein, ""))
		{
			if (file_exists(ctable->filein) == 0)
			{
				print("minishell: ", 2);
				print(ctable->filein, 2);
				print(": No such file or directory\n", 2);
				return(-1);
			}
			ctable->in = open(ctable->filein, O_RDONLY);
		}
	}
	return (0);
}

int	token_to_command(c_table *ctable, char **tokens)
{
	(void)ctable;
	if (is_redirec(*tokens) != 0)
	{
		if (redirection(ctable, tokens++) < 0)
			return (-1);
		return (1);
	}
	else
	{
		ctable->args = expanse_array(ctable->args, ctable->args_len, *tokens);	
		if (ctable->command_exists == 0)
			ctable->command = ft_strdup(ctable->args[0]);
		ctable->command_exists = 1;
		ctable->args_len++;
	}
	return (0);
}

int			parser(c_table *ctable, char **tokens)
{
	int	*status;
	int	result;

	result = 0;
	status = (int*)getglobal(STATUS);
	while (*tokens)
	{
		if ((ctable->separator = separator(*tokens)) != 0)
		{
			ctable->command_exists = 0;
			add_struct(&ctable);
		}
		if (is_pipe(*tokens, ctable))
		{
			ctable->command_exists = 0;
			add_struct(&ctable);
		}
		else 
		{
			if ((result = token_to_command(ctable, tokens)) < 0)
				return (-1);
			else if (result == 1)
				tokens++;
		}
		tokens++;
	}
	return (0);	
}