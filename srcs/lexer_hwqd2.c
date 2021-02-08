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
