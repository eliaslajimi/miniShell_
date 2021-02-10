/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:10:46 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/09 08:08:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_lstdelnode(t_list **lst, char *data, int datalen)
{
	t_list	*current;
	t_list	*previous;

	previous = NULL;
	current = *lst;
	while (current)
	{
		if (ft_strncmp(current->content, data, datalen) == 0 &&
				(ft_strncmp((char*)(current->content) + datalen, "=", 1)) == 0)
		{
			if (previous == NULL)
				*lst = current->next;
			else
				previous->next = current->next;
			free(current->content);
			free(current);
			return (0);
		}
		if (current->next == NULL)
			break ;
		previous = current;
		current = current->next;
	}
	return (127);
}

int			unset_builtin(char *arg, char *exportarg)
{
	int		k;
	int		ret;
	int		arglen;
	char	*param;

	k = 0;
	ret = 0;
	if (arg[0] == '\0')
		return (p("minishell: unset: `': not a valid identifier\n", 0, 0) + 2);
	while (arg[k])
	{
		if (ft_isin(arg[k], "\'\"\\$@!|;&= "))
		{
			return (p("minishell: unset: `",
			arg, "': not a valid identifier\n") + 2);
		}
		k++;
	}
	if (ft_strcmp(arg, "") != 0)
	{
		param = (ft_strcmp(exportarg, "void") == 0) ? arg : exportarg;
		arglen = ft_strlen(param);
		ret = ft_lstdelnode(&g_env, param, arglen);
	}
	return (ret);
}

int			unset_builtin_loop(char **arg, char *exportarg)
{
	int		final_ret;
	int		ret;

	arg++;
	final_ret = 0;
	while (*arg)
	{
		ret = unset_builtin(*arg, exportarg);
		if (ret != 0)
			final_ret = ret;
		arg++;
	}
	arg--;
	add_underscore(*arg);
	return (final_ret);
}
