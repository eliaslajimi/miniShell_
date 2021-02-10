/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:02:52 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 14:02:57 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*check_token(char *line)
{
	if (*line == '|')
		return (pipe_token(line));
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
	if (!(cpy = ft_calloc(sizeof(char*), (previous_size + 1 + 1))))
		return (NULL);
	while (i < previous_size)
	{
		cpy[i] = ft_strdup(array[i]);
		free(array[i]);
		i++;
	}
	cpy[i++] = ft_strdup(new_token);
	free(new_token);
	free(array);
	array = NULL;
	return (cpy);
}

static char	**lex_line(char **tab, char *input_line)
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
			if (ft_isprint(input_line[i]) == 1 &&
			!(ft_isin(input_line[i], "|<>")))
				i_word = word_token_len(input_line + i);
			if ((token = check_token(input_line + i)) == NULL)
				return (NULL);
			i = (i_word == 0) ? i + ft_strlen(token) : i + i_word;
			if (!(tab = expanse_array(tab, array_size, token)))
				return (NULL);
			array_size++;
		}
	}
	return (tab);
}

char		**lexer(char *input_line)
{
	char	**isolated_tokens;

	isolated_tokens = NULL;
	if (!ft_strlen(input_line))
		return (NULL);
	//if (!(isolated_tokens = ft_calloc(sizeof(char *), 1)))
	//	return (NULL);
	if ((isolated_tokens = lex_line(isolated_tokens, input_line)) == NULL)
		return (NULL);
	return (isolated_tokens);
}
