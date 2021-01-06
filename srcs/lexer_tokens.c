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

char		*handling_word_quotes_dollar(char *word)
{
	int		i;
	int		len;
	char	*result;
	int		*status;
	char	*str_status;

	i = 0;
	result = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '\'')
		{
			i++;
			while (word[i] && word[i] != '\'')
				result = ft_strjoin_char(result, word[i++]);
			i++;
		}
		else if (word[i] == '\"')
		{
			i++;
			while (word[i] && word[i] != '\"')
			{
				if (word[i] != '$')
					result = ft_strjoin_char(result, word[i++]);
				else if (word[i] == '$')
				{
					if (word[i + 1] == '?')
					{
						i += 2;
						status = (int*)getglobal(STATUS);
						str_status = ft_itoa(*status);
						result = ft_strjoin(result, str_status);
					}
					else
					{
						i++;
						len = 0;
						while (word[i] != '$' && word[i] != '\"' && word[i] != '\'')
						{
							len++;
							i++;
						}
						if (swap_dollar(word, i - len, len) != NULL)
						{
							result = ft_strjoin(result, swap_dollar(word, i - len, len));
						}
						else
							result = ft_strjoin(result, "");
					}
				}
			}
			i++;
		}
		else if (word[i] == '$')
		{
			if (word[i + 1] == '?')
			{
				i += 2;
				status = (int*)getglobal(STATUS);
				str_status = ft_itoa(*status);
				result = ft_strjoin(result, str_status);
			}
			else
			{
				i++;
				len = 0;
				while (word[i] && word[i] != '$' && word[i] != '\"' && word[i] != '\'')
				{
					len++;
					i++;
				}
				if (swap_dollar(word, i - len, len) != NULL)
				{
					result = ft_strjoin(result, swap_dollar(word, i - len, len));
				}
				else
				{
					result = ft_strjoin(result, "");
				}
			}
		}
		else
		{
			result = ft_strjoin_char(result, word[i++]);
		}
	}
	return (result);
}

int			word_token_len(char *line)
{
	int		i;	
	char	quote_type;

	i = 0;
	while (ft_isprint(line[i]) == 1 && !(ft_isin(line[i]," &;|><")))
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
	while (ft_isprint(line[i]) == 1 && !(ft_isin(line[i]," &;|><")))
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
	token = handling_word_quotes_dollar(token);
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
