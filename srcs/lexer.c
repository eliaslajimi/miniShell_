#include "minishell.h"

char *check_token(char *line)
{
	if (*line == '|')
		return (pipe_token(line));
	else if (*line == ';')
		return (semic_token(line));
	else if (*line == '>' || *line == '<')
		return (redirec_token(line));
	else if (ft_isprint(*line) == 1)
	{
		return (word_token(line));
	}
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
	int		i_word;
	int		array_size;
	char	*token;

	i = 0;
	array_size = 0;
	while (input_line[i])
	{
		//printf("HERE input_line %s\n", input_line);
		i += skip_spaces(input_line + i);
		//printf("HERE input_line + i %s\n", input_line + i);
		if (input_line[i] != '\0')
		{
			i_word = 0;
			if (ft_isprint(input_line[i]) == 1 && !(ft_isin(input_line[i], "|;<>")))
				i_word = word_token_len(input_line + i);
			//printf("word of len %d\n", i_word);
			if ((token = check_token(input_line + i)) == NULL)
				return (NULL);
			if (i_word == 0)
				i += ft_strlen(token);
			else
				i += i_word;
		//	printf("adding token %s\n", token);
			isolated_tokens = expanse_array(isolated_tokens, array_size, token);
			array_size++;
		}
	}
	ft_strdel(&input_line);
	return (isolated_tokens);
}

char		**lexer(char *input_line)
{
	char	**isolated_tokens;

	//printf("inputline [%s]\n", input_line);
	if (!ft_strlen(input_line))
		return (NULL);
	input_line = matching_quotes(input_line);
	//printf("mq inputline %s\n", input_line);

	if (!(isolated_tokens = malloc(sizeof(char *) * (1))))
		return (NULL);
	isolated_tokens[0] = NULL;
	if ((isolated_tokens = lex_line(isolated_tokens, input_line)) == NULL)
		return (NULL); // we have to exit because non printable characters (ex with dir. arrows keys.)
/*	int i = 0;
	while (isolated_tokens[i])
		printf("token: %s\n", isolated_tokens[i++]);
	*/return (isolated_tokens);
}
