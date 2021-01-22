/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:53:20 by cmcgahan          #+#    #+#             */
/*   Updated: 2019/10/23 14:22:42 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		nb = (unsigned int)-n;
		ft_putchar_fd('-', fd);
	}
	else
		nb = (unsigned int)n;
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd(nb % 10 + '0', fd);
}
