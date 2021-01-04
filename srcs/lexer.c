#include "minishell.h"

static char *check_token(char *line)
{
	if (*line == '$')
		return (dollar_token(line));
	else if (*line == '|')
		return (pipe_token(line));
	else if (*line == ';')
		return (semic_token(line));
	else if (*line == '>' || *line == '<')
		return (redirec_token(line));
	else if (*line == 34 || *line == 39)
		return (quote_token(line));
	else if (ft_isprint(*line) == 1)
		return (word_token(line));
	else
		return (NULL);
}

char		**expanse_array(char **array, int previous_size, char *new_token)
{
	int		i;
	char	**cpy;

	i = 0;
	if (!(cpy = malloc(sizeof(char*) * (previous_size + 1 + 1))))
		return (NULL);
	while (i < previous_size)
	{
		cpy[i] = ft_strdup(array[i]);
		ft_strdel(&array[i]);
		i++;
	}
	cpy[i++] = ft_strdup(new_token);
	ft_strdel(&new_token);
	cpy[i] = NULL;
	free(array);
	array = NULL;
	return (cpy);
}

static char	**lex_line(char **isolated_tokens, char *input_line)
{
	int		i;
	int		array_size;
	char	*token;

	i = 0;
	array_size = 0;
	while (input_line[i])
	{
		i += skip_spaces(input_line + i);
		if (input_line[i] != '\0')
		{
			token = check_token(input_line + i);
			i += ft_strlen(token);
			isolated_tokens = expanse_array(isolated_tokens, array_size, token);
			array_size++;
		}
	}
	return (isolated_tokens);
}

char		**lexer(char *input_line)
{
	char	**isolated_tokens;

	input_line = matching_quotes(input_line);
	if (!(isolated_tokens = malloc(sizeof(char *) * (1))))
		return (NULL);
	isolated_tokens[0] = NULL;
	isolated_tokens = lex_line(isolated_tokens, input_line);
	return (isolated_tokens);
}
