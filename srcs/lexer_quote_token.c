/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:28:18 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/10 06:39:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char		*matching_quotes(char *line)
{
	int		i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (NULL);
	while (line[i])
	{
		while (line[i] && line[i] != '\"' && line[i] != '\'' && line[i] != '\\')
			i++;
		if (line[i] == '\"')
		{
			i += skip_quote_lexer(line + i, '\"');
			if (i == ft_strlen(line) + 1)
				return (matching_quotes(inputline_join(line)));
		}
		else if (line[i] == '\'')
		{
			i += skip_quote_lexer(line + i, '\'');
			if (i == ft_strlen(line) + 1)
				return (matching_quotes(inputline_join(line)));
		}
		else if (line[i] == '\\')
			i += 2;
	}
	return (line);
}
