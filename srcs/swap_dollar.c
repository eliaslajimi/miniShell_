/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:33:30 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 15:33:31 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*handlspace(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = 0;
	j = 0;
	len = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == ' ')
		{
			result[j] = ' ';
			j++;
			while (str[i] == ' ')
				i++;
		}
		result[j++] = str[i++];
	}
	result[j] = 0;
	len = ft_strlen(result);
	if (result[0] == '\0' && len != 0)
		result = ft_strdup(" ");
	return (result);
}

char		*swap_dollar(char *s, int i, int len, int quotes)
{
	char	*tmp;
	char	*tofind;
	char	*result;

	tofind = ft_strndup(s + i, len);
	if (find_node(tofind) != NULL)
	{
		result = ft_strdup(find_node(tofind) + ft_strlen(tofind) + 1);
		if (quotes == 1)
		{
			tmp = result;
			result = handlspace(tmp);
			free(tmp);
		}
		ft_strdel(&tofind);
		return (result);
	}
	free(tofind);
	return (NULL);
}
