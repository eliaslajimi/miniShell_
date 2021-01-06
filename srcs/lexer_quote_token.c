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
		skip++;
	return (skip + 1);
}

char	*matching_quotes(char *line)
{
	int	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != 34 && line[i] != 39)
			i++;
		if (line[i] == 34)
		{
			i += skip_quote_lexer(line + i, 34);
			if (i == ft_strlen(line) + 1)
			{
				line = inputline_join(line);
				return (matching_quotes(line));
			}
		}
		else if (line[i] == 39)
		{
			i += skip_quote_lexer(line + i, 39);
			if (i == ft_strlen(line) + 1)
			{
				line = inputline_join(line);
				return (matching_quotes(line));
			}
		}
	}
	return (line);
}
