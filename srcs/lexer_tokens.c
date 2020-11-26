#include "minishell.h"

char		*dollar_token(char *line)
{
	int		i;
	char	*token;

	i = 1;
	if (line[i] == '?')
		token = ft_strdup("$?");
	else if (line[1] == ' ')
		token = ft_strdup("$");
	else if (ft_isprint(line[i]) == 1)
	{
		while (ft_isprint(line[i]) == 1 && line[i] != ' ')
			i++;
		token = ft_strndup(line, i);
	}
	return (token);
}

char		*word_token(char *line)
{
	int		i;
	char	*token;

	i = 0;
	while (ft_isprint(line[i]) == 1 && line[i] != ' ')
		i++;
	token = ft_strndup(line, i);
	return (token);
}

char	*pipe_token(char *line)
{
	char	*token;

	token = ft_strdup("|");
	return (token);
}

char	*semic_token(char *line)
{
	char	*token;

	token = ft_strdup(";");
	return (token);
}

char	*redirec_token(char *line)
{
	char *token;

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
