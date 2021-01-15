#include "minishell.h"

static char	*inputline_join(char *line)
{
	char	*join;
	char	*str;

	write(1, "dquote>", 7);
	get_next_line(1, &str);
	join = ft_strjoin(line, str);
	ft_strdel(&str);
	return (join);
}

static int		skip_quote_lexer(char *line, char quote)
{
	int skip;

	skip = 1;
	while (line[skip] && line[skip] != quote)
	{
		if (quote == '\"' && line[skip] == '\\')
		{
//			if (line[skip + 1] == quote)
				skip += 2;
		}
		else
			skip++;
	}
	return (skip + 1);
}

char	*matching_quotes(char *line)
{
	int	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '\"' && line[i] != '\'' && line[i] != '\\')
			i++;
		if (line[i] == '\"')
		{
			i += skip_quote_lexer(line + i, '\"');
			if (i == ft_strlen(line) + 1)
			{
				line = inputline_join(line);
				return (matching_quotes(line));
			}
		}
		else if (line[i] == '\'')
		{
			i += skip_quote_lexer(line + i, '\'');
			if (i == ft_strlen(line) + 1)
			{
				line = inputline_join(line);
				return (matching_quotes(line));
			}
		}
		else if (line[i] == '\\')
		{
//			if (line[i + 1] == '\'' || line[i + 1] == '\"')
				i += 2;
//			else
//				i++;
		}
	}
	return (line);
}
