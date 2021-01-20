#include "minishell.h"

static int		check_next_token(char **tokens, int i)
{
	if (ft_strcmp(tokens[i + 1], ">") == 0)
		return (1);
	else if (ft_strcmp(tokens[i + 1], "<") == 0)
		return(2);
	else if (ft_strcmp(tokens[i + 1], ";") == 0)
		return(3);
	else if (ft_strcmp(tokens[i + 1], "|") == 0)
		return(4);
	return (0);
}

static int	print_prob(int prob)
{
	if (prob == 1)
	{
		print("minishell: syntax error near unexpected token `>'\n", 2);
		return(2);
	}
	else if (prob == 2)
	{
		print("minishell: syntax error near unexpected token `<'\n", 2);
		return(2);
	}
	else if (prob == 3)
	{
		print("minishell: syntax error near unexpected token `;'\n", 2);
		return(2);
	}
	else if (prob == 4)
	{
		print("minishell: syntax error near unexpected token `|'\n", 2);
		return(2);
	}
	return (0);
}
static int	lexer_check_symbols(char **tokens)
{
	int 	i;
	int		prob;

	i = 0;
	prob = 0;
	while (tokens[i] && prob == 0)
	{
		if (ft_strcmp(tokens[i], ">") == 0 )
			prob = check_next_token(tokens, i);
		else if (ft_strcmp(tokens[i], "<") == 0)
			prob = check_next_token(tokens, i);
		else if (ft_strcmp(tokens[i], ";") == 0)
			prob = check_next_token(tokens, i);
		else if (ft_strcmp(tokens[i], "|") == 0)
			prob = check_next_token(tokens, i);
		else if (ft_strcmp(tokens[i], ">>") == 0)
			prob = check_next_token(tokens, i);
		i++;
	}
	
	if (prob != 0)
		return(print_prob(prob));
	return (0);
}

static char	**lex_line_special(char **isolated_tokens, char *input_line)
{
	int		i;
	int		i_word;
	int		array_size;
	char	*token;

	i = 0;
	array_size = 0;
	while (input_line[i])
	{
		i += skip_spaces(input_line + i);
		if (input_line[i] != '\0')
		{
			i_word = 0;
			if (ft_isprint(input_line[i]) == 1 && !(ft_isin(input_line[i], "|;<>")))
				i_word = word_token_len(input_line + i);
			if ((token = check_token(input_line + i)) == NULL)
				return (NULL);
			if (i_word == 0)
				i += ft_strlen(token);
			else
				i += i_word;
			isolated_tokens = expanse_array(isolated_tokens, array_size, token);
			array_size++;
		}
	}
	return (isolated_tokens);
}

int			lexer_special(char *input_line)
{
	int		lexer_check_status;
	char	**isolated_tokens;

	lexer_check_status = 0;
	if (!ft_strlen(input_line))
		return (-1);
	input_line = matching_quotes(input_line);
	if (!(isolated_tokens = malloc(sizeof(char *) * (1))))
		return (-1);
	isolated_tokens[0] = NULL;
	if ((isolated_tokens = lex_line_special(isolated_tokens, input_line)) == NULL)
		return (-1); // we have to exit because non printable characters (ex with dir. arrows keys.)
	lexer_check_status = lexer_check_symbols(isolated_tokens);
	return (lexer_check_status);
}