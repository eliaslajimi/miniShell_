/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:41:23 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/01/28 14:43:23 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_lstfree(t_list *head)
{
	t_list	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}
