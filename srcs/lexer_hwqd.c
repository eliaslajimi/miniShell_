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

static void	dollar(t_hwqd *v, char *word)
{
	char	*res_swap_dollar;

	if (word[v->i + 1] == '?')
	{
		v->i += 2;
		v->status = (int*)getglobal(STATUS);
		v->str_status = ft_itoa(*(v->status));
		v->result = ft_strjoin(v->result, v->str_status);
	}
	else if (word[v->i + 1] == '_' && ft_isalpha(word[v->i + 2]) == 0 && word[v->i + 2] != '_')
	{
		v->i += 2;
	//	printf("find node [%s]\n", find_node("_"));
		v->result = ft_strjoin(v->result, cleannode(find_node("_")));
	}
	else
	{
		v->i++;
		v->len = 0;
		while (word[v->i] && word[v->i] != '$' && word[v->i] != '\"' && word[v->i] != '\''
		&& word[v->i] != ',' && word[v->i] != '[' && word[v->i] != ']' && word[v->i] != '\\' && word[v->i] != '@')
		{
			v->len++;
			v->i++;
		}
		res_swap_dollar = swap_dollar(word, v->i - v->len, v->len);
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
}

static void	double_quote2(t_hwqd *v, char *word)
{
	//printf("we here [%s]\n", word);
	if (word[v->i + 1] == '?')
	{
		v->i += 2;
		v->status = (int*)getglobal(STATUS);
		v->str_status = ft_itoa(*(v->status));
		v->result = ft_strjoin(v->result, v->str_status);
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
		while (word[v->i] != '$' && word[v->i] != '\"' && word[v->i] != '\'' && word[v->i] != '|'
		&& word[v->i] != ',' && word[v->i] != ']' && word[v->i] != '[' && word[v->i] != '@' && word[v->i] != '\\')
		{
			v->len++;
			v->i++;
		}
		if (swap_dollar(word, v->i - v->len, v->len) != NULL)
		{
			v->result = ft_strjoin(v->result, swap_dollar(word, v->i - v->len, v->len));
		}
		else
			v->result = ft_strjoin(v->result, "");
	}
}

static void	double_quote(t_hwqd *v, char *word)
{
	v->i++;
	//printf("word double quote [%s]\n", word);
	//printf("word double quote [%s]\n", word + v->i);

	while (word[v->i] && word[v->i] != '\"')
	{
		if (word[v->i] == '\\')
	   	{
		   	if ( word[v->i + 1] == '\"' || word[v->i + 1] == '\\'
			   || word[v->i + 1] == '$')
		   	{
			   	v->i++;
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
				v->result = ft_strjoin_char(v->result, word[v->i++]);
				v->result = ft_strjoin_char(v->result, word[v->i++]);
			}
	   	}
		else if (word[v->i] != '$')
			v->result = ft_strjoin_char(v->result, word[v->i++]);
		else // if its a dollar
	   		double_quote2(v, word);
	}
	v->i++;
}

static void	single_quote(t_hwqd *v, char *word)
{
	v->i++;
	while (word[v->i] && word[v->i] != '\'')
		v->result = ft_strjoin_char(v->result, word[v->i++]);
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
	//printf("word hwqd: [%s]\n", word);
	while (word[v->i])
	{
		if (word[v->i] == '\'')
			single_quote(v, word);
		else if (word[v->i] == '\"')
		{
			double_quote(v, word);
		}
		else if (word[v->i] == '$')
		{
			//printf("dollar\n");
			if (word[v->i + 1] == '\\' || word[v->i + 1] == '\0' || word[v->i + 1] == '%')
			{
				v->result = ft_strjoin_char(v->result, word[v->i++]);
			//	printf("result now : [%s]\n", v->result);
				//v->i++;
			}
			else
			{
				//printf("found dollar\n");
				dollar(v, word);
			}
		}
		else if (word[v->i] == '\\')
		{
			v->i++;
			if (word[v->i] == 'r' || word[v->i] == 't' ||
					word[v->i] == 'v' || word[v->i] == 'f')
				v->i++;
			else
				v->result = ft_strjoin_char(v->result, word[v->i++]);
			//printf("result now : [%s]\n", v->result);
		}
		else
			v->result = ft_strjoin_char(v->result, word[v->i++]);
	}
	result = ft_strdup(v->result);
	free(v->result);
	free(v);
	free(word);
	return (result);
}
