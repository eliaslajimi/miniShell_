/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elajimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:39:02 by elajimi           #+#    #+#             */
/*   Updated: 2020/02/17 16:48:54 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strfiller(char *result, char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		++i;
	}
	while (s2[j])
	{
		result[i] = s2[j];
		++i;
		++j;
	}
	result[i] = '\0';
	return (result);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;
	char	*result;

	if (s1 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(result = (char*)malloc(((i + j) + 1) * sizeof(char))))
		return (0);
	result = ft_strfiller(result, s1, s2);
	free(s1);
	return (result);
}
