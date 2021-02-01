/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 13:18:23 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/12/07 15:16:41 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlist;

	if (!(newlist = (t_list *)malloc(sizeof(t_list) + 1)))
		return (NULL);
	if (!content)
		newlist->content = NULL;
	else
	{
		if (!(newlist->content = ft_strdup(content)))
			return (NULL);
	}
	newlist->next = NULL;
	return (newlist);
}
