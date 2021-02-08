/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:35:13 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 14:35:14 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_next_token(char **tokens, int i)
{
	if (!tokens[i + 1] && ft_strcmp(tokens[i], ";") == 0)
		return (0);
	if (((tokens[i + 1] == NULL) || (ft_strcmp(tokens[i + 1], ">") == 0)))
	{
		if (tokens[i + 1] == NULL)
			return (7);
		return (1);
	}
	else if (ft_strcmp(tokens[i + 1], "<") == 0)
		return (2);
	else if (ft_strcmp(tokens[i + 1], ";") == 0)
		return (3);
	else if (ft_strcmp(tokens[i + 1], "|") == 0)
		return (4);
	else if (ft_strcmp(tokens[i + 1], ">>") == 0)
		return (5);
	else if (ft_strcmp(tokens[i + 1], "<<") == 0)
		return (6);
	if (!tokens[i + 1])
		return (0);
	return (0);
}

static int	print_prob(int prob)
{
	if (prob == 1)
		print("minishell: syntax error near unexpected token `>'\n", 2);
	else if (prob == 2)
		print("minishell: syntax error near unexpected token `<'\n", 2);
	else if (prob == 3)
		print("minishell: syntax error near unexpected token `;'\n", 2);
	else if (prob == 4)
		print("minishell: syntax error near unexpected token `|'\n", 2);
	else if (prob == 5)
		print("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (prob == 6)
		print("minishell: syntax error near unexpected token `<<'\n", 2);
	else if (prob == 7)
		print("minishell: syntax error near unexpected token `newline'\n", 2);
	if (prob != 0)
		return (2);
	return (0);
}

static int	lexer_check_symbols(char **tokens)
{
	int		i;
	int		prob;

	i = 0;
	prob = 0;
	while (tokens[i] && prob == 0)
	{
		if (ft_strcmp(tokens[i], ">") == 0)
			prob = check_next_token(tokens, i);
		else if (ft_strcmp(tokens[i], "<") == 0)
			prob = check_next_token(tokens, i);
		else if (ft_strcmp(tokens[i], ";") == 0)
			prob = check_next_token(tokens, i);
		else if (ft_strcmp(tokens[i], "|") == 0)
			prob = check_next_token(tokens, i);
		else if (ft_strcmp(tokens[i], ">>") == 0)
			prob = check_next_token(tokens, i);
		else if (ft_strcmp(tokens[i], "<<") == 0)
			prob = check_next_token(tokens, i);
		i++;
	}
	if (prob != 0)
		return (print_prob(prob));
	return (0);
}

static char	**lex_line_special(char **isolated_tokens, char *input)
{
	int		i;
	int		i_word;
	int		array_size;
	char	*token;

	i = 0;
	array_size = 0;
	while (input[i])
	{
		i += skip_spaces(input + i);
		if (input[i] != '\0')
		{
			i_word = 0;
			if (ft_isprint(input[i]) == 1 && !(ft_isin(input[i], "|;<>")))
				i_word = word_token_len(input + i);
			if ((token = check_token(input + i)) == NULL)
				return (NULL);
			i = (i_word == 0) ? i + ft_strlen(token) : i + i_word;
			isolated_tokens = expanse_array(isolated_tokens, array_size, token);
			array_size++;
		}
	}
	return (isolated_tokens);
}

int			lexer_special(char *input_line)
{
	char	*matched_line;
	int		lexer_check_status;
	char	**isolated_tokens;

	lexer_check_status = 0;
	if (!ft_strlen(input_line))
		return (-1);
	matched_line = ft_strdup(input_line);
	if (!(isolated_tokens = malloc(sizeof(char *) * (1))))
		return (-1);
	isolated_tokens[0] = NULL;
	if ((isolated_tokens =
	lex_line_special(isolated_tokens, matched_line)) == NULL)
	{
		free(matched_line);
		return (-1);
	}
	free(matched_line);
	lexer_check_status = lexer_check_symbols(isolated_tokens);
	ft_free_array(isolated_tokens);
	return (lexer_check_status);
}
