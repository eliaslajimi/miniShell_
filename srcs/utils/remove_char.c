/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:30:37 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/01/28 14:30:39 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Removes the char at a specific position in a string
*/

char		*remove_char_pos(char *str, int pos)
{
	int		i;
	int		j;
	char	*clean_str;

	i = 0;
	j = 0;
	if (!(clean_str = malloc(sizeof(char) * (ft_strlen(str) - 1 + 1))))
		return (NULL);
	while (str[i] && i < ft_strlen(str))
	{
		if (i != pos)
			clean_str[j++] = str[i];
		i++;
	}
	clean_str[j] = '\0';
	ft_strdel(&str);
	return (clean_str);
}

/*
** Removes first occurence of a char in a string
*/

char		*remove_char(char *str, char c)
{
	int		i;
	int		j;
	int		pos_c;
	char	*clean_str;

	i = -1;
	pos_c = 0;
	while (str[++i])
	{
		if (str[i] == c)
		{
			pos_c = i;
			if (!(clean_str = ft_calloc(sizeof(char), (ft_strlen(str)))))
				return (NULL);
			i = -1;
			j = 0;
			while (str[++i])
				if (i != pos_c)
					clean_str[j++] = str[i];
			ft_strdel(&str);
			return (clean_str);
		}
	}
	return (str);
}

/*
**	Removes every occurence of a char in a string
*/

char		*remove_all_char(char *str, char toremove)
{
	int		i;
	int		j;
	int		remove;
	char	*clean_str;

	i = -1;
	remove = 0;
	while (str[++i])
		if (str[i] == toremove)
			remove++;
	if (!(clean_str = ft_calloc(sizeof(char), (ft_strlen(str) - remove) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != toremove)
			clean_str[j++] = str[i];
		i++;
	}
	ft_strdel(&str);
	return (clean_str);
}
