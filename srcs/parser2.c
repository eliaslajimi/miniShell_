/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:22:40 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 15:22:41 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_redirec(char *token)
{
	return (ft_strcmp(token, ">>") == 0 || ft_strcmp(token, ">") == 0
	|| ft_strcmp(token, "<") == 0);
}

int			is_pipe(char *token, t_table *ctable)
{
	if (ft_strcmp(token, "|") == 0)
		return ((ctable->pipeout = 1));
	return (0);
}

int			is_quote(char c)
{
	if (c == 96 || c == 39 || c == 34)
		return (c);
	return (0);
}

char		*is_subshell(char *token)
{
	char	*str;

	str = malloc(2);
	if (is_quote(token[0]))
	{
		str[1] = 0;
		str[0] = token[0];
		return (str);
	}
	return (NULL);
}

int			separator(char *token)
{
	if (ft_strcmp(token, ";") == 0)
		return (COMMA);
	else if (ft_strncmp(token, "&&", 2) == 0)
		return (AMPERSAND);
	return (0);
}
