/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elajimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:11:09 by elajimi           #+#    #+#             */
/*   Updated: 2019/10/28 15:55:24 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		ft_match(char const *s1, char const *set)
{
	int j;
	int counter;
	int i;
	int boolean;

	j = 0;
	i = 0;
	boolean = 1;
	counter = 1;
	while (s1[i] && boolean == 1)
	{
		boolean = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				boolean = 1;
				++counter;
			}
			++j;
		}
		++i;
		j = 0;
	}
	return (counter);
}

static int		ft_reversematch(char const *s1, char const *set)
{
	int j;
	int i;
	int counter;
	int boolean;

	boolean = 1;
	j = ft_strlen((char*)s1);
	i = ft_strlen((char*)set);
	counter = 0;
	while (j > 0 && boolean == 1)
	{
		boolean = 0;
		while (i >= 0)
		{
			if (s1[j] == set[i])
			{
				boolean = 1;
				++counter;
			}
			--i;
		}
		i = ft_strlen((char*)set) - 1;
		j--;
	}
	return (counter);
}

static void		fillmalloc(char *result, const char *s1, int start, int s1len)
{
	int i;

	i = 0;
	while (i < s1len)
	{
		result[i] = s1[start];
		++i;
		++start;
	}
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		counter;
	int		s1len;
	int		resultlen;
	int		start;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	counter = ft_match(s1, set);
	s1len = ft_strlen((char*)s1);
	start = counter - 1;
	counter += ft_reversematch(s1, set);
	resultlen = s1len - counter + 1;
	resultlen = (resultlen > 0) ? resultlen : 0;
	if (!(result = (char*)malloc((resultlen + 2) * sizeof(char))))
		return (0);
	fillmalloc(result, s1, start, resultlen + 1);
	result[resultlen + 1] = '\0';
	return (result);
}
