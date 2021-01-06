#include "minishell.h"

char		*dollar_token(char *line)
{
	int		i;
	char	*token;

	i = 1;
	token = "";
	if (line[i] == '?')
		token = ft_strdup("$?");
	else if (line[1] == ' ')
		token = ft_strdup("$");
	else if (ft_isprint(line[i]) == 1 && !(ft_isin(line[i]," &;|><$\'\"")))
	{
		while (ft_isprint(line[i]) == 1 && !(ft_isin(line[i]," &;|><$\'\"")))
			i++;
		token = ft_strndup(line, i);
	}
	return (token);
}

char		*handling_word_quotes(char *word)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	result = ft_strdup(word);
	while (result[i])
	{
//		printf("entering here, word i = [%c], i = [%d]\n", word[i], i);

		if (result[i] == '\'')
		{
			result = remove_char_pos(result, i);
			while (result[i] && result[i] != '\'')
				i++;
			result = remove_char_pos(result, i);
		}
		else if (result[i] == '\"')
		{
			result = remove_char_pos(result, i);
			while (result[i] && result[i] != '\"')
			{
				if (result[i] != '$')
					i++;
				else if (result[i] == '$')
				{
					len = 0;
					while (result[i] != '$' && result[i] != '\"' && result[i] != '\'')
					{
						len++;
						i++;
					}
					if (swap_dollar(result, i - len, len) != NULL)
						result = ft_strjoin(result, swap_dollar(result, i - len, len));
					else
						result = ft_strjoin(result, "");
				i += len;
				}

			}
			result = remove_char_pos(result,i);
		}
		else
		{
			i++;
		}
//		printf("		on reboucle avec i = %d\n", i);
	}
//	printf("RESULT IS %s\n", result);
//	sleep(1);
	return (result);
}

int			word_token_len(char *line)
{
	int		i;	
	char	quote_type;

	i = 0;
//	printf("testing the line [%s]\n", line);
	while (ft_isprint(line[i]) == 1 && !(ft_isin(line[i]," &;|><$")))
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote_type = line[i++];
			while (line[i] && line[i] != quote_type)
				i++;
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
	while (ft_isprint(line[i]) == 1 && !(ft_isin(line[i]," &;|><$")))
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote_type = line[i++];
			while (line[i] && line[i] != quote_type)
				i++;
		}
		i++;
	}
	token = ft_strndup(line, i);
	token = handling_word_quotes(token);
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
