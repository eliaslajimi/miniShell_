/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_hwqd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:49:38 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/09 05:42:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		double_quote2(t_hwqd *v, char *word)
{
	if (word[v->i + 1] == '?')
	{
		v->i += 2;
		v->result = ft_strjoin(v->result, ft_itoa(*((int*)getglobal(STATUS))));
	}
	else if (word[v->i + 1] == '\\' || word[v->i + 1] == '\0')
	{
		v->result = ft_strjoin_char(v->result, word[v->i++]);
		v->i++;
	}
	else
	{
		v->i++;
		v->len = 0;
		while (ft_isin(word[v->i], "$\"\'|,][@\\") == 0)
		{
			v->len++;
			v->i++;
		}
		if (swap_dollar(word, v->i - v->len, v->len, 0) != NULL)
			v->result = ft_strjoin(v->result,
			swap_dollar(word, v->i - v->len, v->len, 0));
		else
			v->result = ft_strjoin(v->result, "");
	}
}

int			double_quote_more(t_hwqd *v, char *word)
{
	char	*temp;

	if ((word[v->i + 1] == '\"' || word[v->i + 1] == '\\'
		|| word[v->i + 1] == '$') && v->i++)
	{
		v->result = ft_strjoin_char(v->result, word[v->i++]);
	}
	else if (word[v->i + 1] == '\'' || word[v->i + 1] == ' '
	|| word[v->i + 1] == '|' || word[v->i + 1] == '@'
	|| word[v->i + 1] == '!')
	{
		v->result = ft_strjoin_char(v->result, word[v->i++]);
	}
	else if (ft_isalpha(word[v->i + 1]) == 1)
	{
		temp = ft_strjoin_char(v->result, word[v->i]);
		v->i++;
		v->result = ft_strjoin_char(temp, word[v->i]);
		v->i++;
	}
	return (v->i);
}

void		double_quote(t_hwqd *v, char *word)
{
	v->i++;
	while (word[v->i] && word[v->i] != '\"')
	{
		if (word[v->i] == '\\')
		{
			v->i = double_quote_more(v, word);
		}
		else if (word[v->i] != '$')
			v->result = ft_strjoin_char(v->result, word[v->i++]);
		else
			double_quote2(v, word);
	}
	v->i++;
}

char		*handling_word_quotes_dollar(char *word)
{
	char	*result;
	t_hwqd	*v;

	if (!(v = malloc(sizeof(t_hwqd))))
		return (NULL);
	v->i = 0;
	v->result = ft_strdup("");
	while (word[v->i])
	{
		handling_word_quotes_dollar2(v, word);
	}
	result = ft_strdup(v->result);
	free(v->result);
	free(v);
	free(word);
	return (result);
}
