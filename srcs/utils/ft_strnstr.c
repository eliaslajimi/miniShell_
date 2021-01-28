/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:35:10 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/01/28 14:35:11 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hay;
	char	*need;
	size_t	i;
	size_t	j;

	i = -1;
	hay = (char *)haystack;
	need = (char *)needle;
	if (!(*need))
		return (hay);
	while (hay[++i] && i <= len)
	{
		j = 0;
		while ((hay[i + j] == need[j] || need[j] == 0) && (i + j) <= len)
		{
			if (need[j] == 0)
			{
				while (i--)
					hay++;
				return (hay);
			}
			j++;
		}
	}
	return (0);
}
