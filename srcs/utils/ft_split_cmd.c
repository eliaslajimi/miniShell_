/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:36:57 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 17:13:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char			**ft_free(char **str, int len)
{
	while (len > 0)
	{
		free(str[len]);
		str[len] = NULL;
		len--;
	}
	free(str);
	str = NULL;
	return (NULL);
}

static int			ft_count_words(const char *str)
{
	int				i;
	int				count;

	if (!str)
		return (0);
	i = 0;
	count = (str[i] == '\0') ? 0 : 1;
	while (str[i] && str[i] == ';')
		i++;
	if (i == ft_strlen(str))
		return (0);
	while (str[i])
	{
		if (str[i] == '\"')
			while (str[++i] != '\"')
				;
		if (str[i] == '\'')
			while (str[++i] != '\'')
				;
		if (str[i] == ';' && i > 0 && str[i - 1] != '\\' &&
				str[i + 1] != ';' && str[i + 1] != '\0')
			count += 1;
		i++;
	}
	return (count);
}

static char			**ft_split_cmd2(char *s, char **strsplit, int i, int j)
{
	int				len;

	while (s[i])
	{
		len = 0;
		while (s[i] == ';')
			i++;
		while (s[i])
		{
			if (s[i] == '\'' && s[i - 1] != '\\' && ++len > 0)
				while (s[++i] != '\'')
					len++;
			if (s[i] == '\"' && s[i - 1] != '\\' && ++len > 0)
				while (s[++i] != '\"')
					len++;
			if (s[i] == ';' && i > 0 && s[i - 1] != '\\')
				break ;
			i++;
			len++;
		}
		if (len == 0)
			break ;
		if (++j >= 0 && !(strsplit[j] = ft_substr(s, i - len, len)))
			return (ft_free(strsplit, j));
	}
	return (strsplit);
}

char				**ft_split_cmd(char *s, int *nbr_cmd)
{
	char			**strsplit;
	int				j;

	j = ft_count_words(s);
	*nbr_cmd = j;
	if (s == NULL || !(strsplit = (char **)malloc(sizeof(char *) * j + 1)))
		return (NULL);
	strsplit[j] = NULL;
	return (ft_split_cmd2(s, strsplit, 0, -1));
}
