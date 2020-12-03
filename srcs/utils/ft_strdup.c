/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elajimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:58:13 by elajimi           #+#    #+#             */
/*   Updated: 2019/11/02 22:11:12 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	if ((s2 = malloc(sizeof(*s2) * (i + 1))) != NULL)
	{
		while (s1[j] != '\0')
		{
			s2[j] = s1[j];
			j++;
		}
		s2[j] = '\0';
		return (s2);
	}
	return (NULL);
}

char	*ft_strndup(char const *s1, int n)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && i < n)
		i++;
	if ((s2 = malloc(sizeof(*s2) * (i + 1))) != NULL)
	{
		while (s1[j] != '\0' && j < n)
		{
			s2[j] = s1[j];
			j++;
		}
		s2[j] = '\0';
		return (s2);
	}
	return (NULL);
}
