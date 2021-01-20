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
				i += 2;
	}
	return (line);
}