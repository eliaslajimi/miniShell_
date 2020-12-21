/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elajimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 20:12:35 by elajimi           #+#    #+#             */
/*   Updated: 2019/10/29 16:32:09 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ft_substr(char *s, int start, int len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	else if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	while (s[i] && (int)i < start)
		++i;
	if (!(sub = (char*)malloc(len + 1 * sizeof(char))))
		return (NULL);
	i = 0;
	while ((int)i < len && (int)i < ft_strlen(s) + 1)
	{
		sub[i] = s[start];
		++i;
		++start;
	}
	sub[i] = '\0';
	return (sub);
}
