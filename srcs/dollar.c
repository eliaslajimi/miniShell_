/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:05:20 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 15:05:21 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_words(char *str, char *word)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (str[++i])
		if (ft_strnstr(&str[i], word, ft_strlen(str)) == &str[i])
			count++;
	return (count);
}

char			*interrodollar_swap(char *itoa_id, char *cmd)
{
	size_t		i;
	size_t		j;
	size_t		c;
	char		*result;

	c = count_words(cmd, "$?");
	if (!(result = malloc((ft_strlen(cmd) + c * (ft_strlen(itoa_id) - 2)) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_strlen(cmd) + c * (ft_strlen(itoa_id) - 2))
	{
		if (ft_strncmp(cmd + i, "$?", 2) == 0)
		{
			ft_strcpy(&result[j], itoa_id, ft_strlen(itoa_id));
			i += 2;
			j += ft_strlen(itoa_id);
		}
		else
			result[j++] = cmd[i++];
	}
	result[j] = '\0';
	return (result);
}

char			*dollar_swap(char *tokens)
{
	size_t		split_token_len;
	char		*ret;
	char		*tmp;
	char		**split_tokens;

	split_tokens = ft_split(tokens + 1, '=');
	split_token_len = 0;
	if (((ret = find_node(split_tokens[0])) != NULL))
	{
		split_token_len = ft_strlen(split_tokens[0]);
		tmp = tokens;
		tokens = ft_strdup(ret + split_token_len + 1);
		ft_strdel(&tmp);
		ft_free_array(split_tokens);
		return (tokens);
	}
	else
	{
		ft_strdel(&tokens);
		ft_free_array(split_tokens);
		return (ft_strdup("\n"));
	}
}
