/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:01:55 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 14:01:56 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*cleannode(char *node)
{
	if (!node)
		return (NULL);
	while (*node && *node != '=')
		++node;
	++node;
	return (node);
}

char		*find_node(char *data)
{
	t_list	*iter;
	char	**split_content;

	iter = g_env;
	while (iter && iter->next)
	{
		split_content = ft_split(iter->content, '=');
		if (ft_strcmp(split_content[0], data) == 0)
		{
			ft_free_array(split_content);
			return (iter->content);
		}
		ft_free_array(split_content);
		iter = iter->next;
	}
	split_content = ft_split(iter->content, '=');
	if (ft_strcmp(split_content[0], data) == 0)
	{
		ft_free_array(split_content);
		return (iter->content);
	}
	ft_free_array(split_content);
	return (NULL);
}
