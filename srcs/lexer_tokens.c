#include "minishell.h"

int			word_token_len(char *line)
{
	int		i;	
	char	quote_type;

	i = 0;
	while (ft_isprint(line[i]) == 1)
	{	
		if (line[i] == '\'')
		{
			quote_type = line[i++];
			while (line[i] && line[i] != quote_type)
				i++;
		}
		else if (line[i] == '\\')
			i++;
		else if ((ft_isin(line[i], " ;|><")))
			break;
		else if (line[i] == '&' && line[i + 1] == '&')
			break;
		else if (line[i] == '\"')
		{
			quote_type = line[i++];
			while (line[i] && line[i] != quote_type)
			{
				if (line[i] == '\\')
					i++;
				i++;
			}
		}
		i++;
	}
	return (i);
}

char		*word_token(char *line)
{
	int		i;	
	char	quote_type;
	char	*token;

	i = 0;
	while (ft_isprint(line[i]) == 1)
	{	
		if (line[i] == '\'')
		{
			quote_type = line[i++];
			while (line[i] && line[i] != quote_type)
				i++;
		}
		else if (line[i] == '\\')
			i++;
		else if ((ft_isin(line[i], " ;|><")))
			break;
		else if (line[i] == '&' && line[i + 1] == '&')
			break;
		else if (line[i] == '\"')
		{
			quote_type = line[i++];
			while (line[i] && line[i] != quote_type)
			{
				if (line[i] == '\\')
					i++;
				i++;
			}
		}
		i++;
	}
	token = ft_strndup(line, i);
	//printf("1 token is [%s]\n", token);
	token = handling_word_quotes_dollar(token);
	//printf("2 token is [%s]\n", token);
	return (token);
}

char	*pipe_token()
{
	char	*token;

	token = ft_strdup("|");
	return (token);
}

char	*semic_token()
{
	char	*token;

	token = ft_strdup(";");
	return (token);
}

char	*redirec_token(char *line)
{
	char *token;

	token = "";
	if (line[0] == '>')
	{
		if (line[1] == '>')
			token = ft_strdup(">>");
		else
			token = ft_strdup(">");
	}
	else if (line[0] == '<')
	{
		if (line[1] == '<')
			token = ft_strdup("<<");
		else
			token = ft_strdup("<");
	}
	return (token);
}

char	*quote_token(char *line)
{
	int		i;
	char	quote_type;
	char	*token;

	i = 0;
	quote_type = line[i++];
	while (line[i] && line[i] != quote_type)
		i++;
	token = ft_strndup(line, i + 1);
	return (token);
}
