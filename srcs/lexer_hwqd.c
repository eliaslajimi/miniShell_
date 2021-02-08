/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_hwqd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:49:38 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/01/28 14:50:23 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		dollar2(t_hwqd *v, char *word)
{
	char	*res_swap_dollar;

	v->i++;
	v->len = 0;
	while (word[v->i] && ft_isin(word[v->i], "$\"\',[]\\@") == 0)
	{
		v->len++;
		v->i++;
	}
	res_swap_dollar = swap_dollar(word, v->i - v->len, v->len, 1);
	if (res_swap_dollar != NULL)
	{
		v->result = ft_strjoin(v->result, res_swap_dollar);
	}
	else
	{
		v->result = ft_strjoin(v->result, "");
	}
	free(res_swap_dollar);
}

void		dollar(t_hwqd *v, char *word)
{
	if (word[v->i + 1] == '?')
	{
		v->i += 2;
		v->status = (int*)getglobal(STATUS);
		v->str_status = ft_itoa(*(v->status));
		v->result = ft_strjoin(v->result, v->str_status);
	}
	else if (word[v->i + 1] == '_' &&
	ft_isalpha(word[v->i + 2]) == 0 && word[v->i + 2] != '_')
	{
		v->i += 2;
		v->result = ft_strjoin(v->result, cleannode(find_node("_")));
	}
	else
	{
		dollar2(v, word);
	}
}

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

void		double_quote(t_hwqd *v, char *word)
{
	v->i++;
	while (word[v->i] && word[v->i] != '\"')
	{
		if (word[v->i] == '\\')
		{
			if (word[v->i + 1] == '\"' || word[v->i + 1] == '\\'
				|| word[v->i + 1] == '$')
			{
				v->i++;
				v->result = ft_strjoin_char(v->result, word[v->i++]);
			}
			else if (word[v->i + 1] == '\'' || word[v->i + 1] == ' '
			|| word[v->i + 1] == '|' || word[v->i + 1] == '@'
			|| word[v->i + 1] == '!')
				v->result = ft_strjoin_char(v->result, word[v->i++]);
			else if (ft_isalpha(word[v->i + 1]) == 1)
				v->result = ft_strjoin_char(ft_strjoin_char(
					v->result, word[v->i++]), word[v->i++]);
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
