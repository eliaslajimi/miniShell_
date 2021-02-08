/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:05:16 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 15:05:17 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			echo2(char **arg, int args_len, int out)
{
	int		i;
	int		j;
	int		nflag;

	i = 0;
	nflag = 0;
	while (++i < args_len && (ft_strncmp(arg[i], "-n", 2) == 0))
		nflag = 1;
	j = i;
	while (i++ < args_len)
	{
		if (arg[j])
		{
			print(arg[j++], out);
			if (arg[j])
				print(" ", out);
		}
	}
	j--;
	add_underscore(arg[j]);
	if (nflag == 0)
		print("\n", out);
	if (out > 2)
		close(out);
	return (0);
}

int			echo(char **arg, int args_len, int in, int out)
{
	char	*result;
	char	*buf;
	int		ret;

	ret = 0;
	buf = ft_calloc(10, 1);
	result = ft_calloc(1, 1);
	if (in)
		if ((ret = read(in, buf, 9)) > 0)
			result = ft_strjoin(result, buf);
	free(buf);
	free(result);
	return (echo2(arg, args_len, out));
}
