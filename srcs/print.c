/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:46:48 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/01/28 14:47:34 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			p(char *s1, char *s2, char *s3)
{
	if (s1)
		print(s1, 2);
	if (s2)
		print(s2, 2);
	if (s3)
		print(s3, 2);
	return (-1);
}

int			print(char *s, int fd)
{
	int		ret;

	ret = 1;
	if (s)
		ret = write(fd, s, ft_strlen(s));
	return (ret);
}
