/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 13:17:20 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/12/07 15:16:31 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (alst && new && (*alst != new))
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			tmp = ft_lstlast(*alst);
			tmp->next = new;
		}
	}
}
