/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_hwqd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:27:54 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 14:27:55 by cmcgahan         ###   ########.fr       */
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

void		handling_word_quotes_dollar2(t_hwqd *v, char *word)
{
	if (word[v->i] == '\'')
		single_quote(v, word);
	else if (word[v->i] == '\"')
		double_quote(v, word);
	else if (word[v->i] == '$')
	{
		if (word[v->i + 1] == '\\' ||
		word[v->i + 1] == '\0' || word[v->i + 1] == '%')
			v->result = ft_strjoin_char(v->result, word[v->i++]);
		else
			dollar(v, word);
	}
	else if (word[v->i] == '\\')
	{
		if (ft_isin(word[++v->i], "rtvf"))
			v->result = ft_strjoin_char(v->result, word[v->i++]);
		else
			v->result = ft_strjoin_char(v->result, word[v->i++]);
	}
	else
		v->result = ft_strjoin_char(v->result, word[v->i++]);
}

void		single_quote(t_hwqd *v, char *word)
{
	v->i++;
	while (word[v->i] && word[v->i] != '\'')
		v->result = ft_strjoin_char(v->result, word[v->i++]);
	v->i++;
}
