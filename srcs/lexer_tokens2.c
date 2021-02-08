/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:48:16 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 14:48:17 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_wt(t_wt *t)
{
	t->i = 0;
	t->start = 0;
}

int				word_token_len2(t_wt *t, char *line)
{
	if (line[t->i] == '\\')
	{
		if (ft_isin(line[t->i + 1], "rtvf"))
			return (1);
		t->i++;
	}
	else if ((ft_isin(line[t->i], " |><")))
		return (1);
	else if (line[t->i] == '&' && line[t->i + 1] == '&')
		return (1);
	else if (line[t->i] == '\"')
	{
		t->quote_type = line[t->i++];
		while (line[t->i] && line[t->i] != t->quote_type)
		{
			if (line[t->i] == '\\')
			{
				if (ft_isin(line[t->i + 1], "rtvf"))
					return (1);
				t->i++;
			}
			t->i++;
		}
	}
	return (0);
}

int				word_token_len(char *line)
{
	t_wt		t;

	init_wt(&t);
	while (line[t.i] == '\\')
	{
		if (ft_isin(line[t.i + 1], "rtvf"))
			t.i++;
		else
			break ;
		t.i++;
	}
	while (ft_isprint(line[t.i]) == 1)
	{
		if (line[t.i] == '\'')
		{
			t.quote_type = line[t.i++];
			while (line[t.i] && line[t.i] != t.quote_type)
				t.i++;
		}
		else if (word_token_len2(&t, line) == 1)
			break ;
		t.i++;
	}
	return (t.i);
}

int				word_token2(t_wt *t, char *line)
{
	if (line[t->i] == '\\')
	{
		if (ft_isin(line[t->i + 1], "rtvf"))
			return (1);
		if (line[t->i + 1] == '\0')
		{
			t->i++;
			return (1);
		}
		t->i++;
	}
	else if ((ft_isin(line[t->i], " |><") ||
	(line[t->i] == '&' && line[t->i + 1] == '&')))
		return (1);
	else if (line[t->i] == '\"')
	{
		t->quote_type = line[t->i++];
		while (line[t->i] && line[t->i] != t->quote_type)
		{
			if (line[t->i] == '\\')
				t->i++;
			t->i++;
		}
	}
	return (0);
}

char			*word_token(char *line)
{
	t_wt		t;

	init_wt(&t);
	while (line[t.i] == '\\')
	{
		if (ft_isin(line[t.i + 1], "rtvf"))
			t.i++;
		else
			break ;
		t.i++;
	}
	while (ft_isprint(line[t.i]) == 1)
	{
		if (line[t.i] == '\'')
		{
			t.quote_type = line[t.i++];
			while (line[t.i] && line[t.i] != t.quote_type)
				t.i++;
		}
		else if (word_token2(&t, line) == 1)
			break ;
		t.i++;
	}
	t.token = handling_word_quotes_dollar(ft_strndup(line + t.start, t.i));
	return (t.token);
}
