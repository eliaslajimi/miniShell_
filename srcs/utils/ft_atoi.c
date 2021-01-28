/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:45:09 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/01/28 14:45:43 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int						ft_atoi_minishell(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||\
			str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = 10 * result + str[i] - '0';
		i++;
	}
	result = result * sign;
	return ((int)result);
}

static int				ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
			|| c == '\r' || c == ' ');
}

int						ft_atoi_shlvl(const char *nptr)
{
	int					moins;
	unsigned long long	nbr;

	moins = 1;
	nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*(nptr++) == '-')
			moins *= -1;
	}
	while (*nptr >= '0' && *nptr <= '9')
		nbr = (10 * nbr + (*(nptr++) - 48));
	if (nbr > LONG_MAX)
	{
		errno = ERANGE;
		return (0);
	}
	return ((int)(moins * nbr));
}
