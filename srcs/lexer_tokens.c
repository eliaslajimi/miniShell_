/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:35:39 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/10 10:10:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*pipe_token(char *line)
{
	char		*token;

	if (line)
	{
		token = ft_strdup("|");
		return (token);
	}
	return (NULL);
}

char			*redirec_token(char *line)
{
	char		*token;

	token = "";
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

char			*quote_token(char *line)
{
	int			i;
	char		quote_type;
	char		*token;

	i = 0;
	quote_type = line[i++];
	while (line[i] && line[i] != quote_type)
		i++;
	token = ft_strndup(line, i + 1);
	return (token);
}
