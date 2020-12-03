/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elajimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:17:56 by elajimi           #+#    #+#             */
/*   Updated: 2019/11/02 15:20:51 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(int count, int size)
{
	int i;
	char	*calloc;

	i = 0;
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if ((calloc = malloc(size * count)) != 0)
	{
		while (i < count * size)
		{
			calloc[i] = '\0';
			i++;
		}
		return (calloc);
	}
	return (NULL);
}
