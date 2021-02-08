/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:05:25 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 15:05:26 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*set_env(char **envp)
{
	int		i;
	t_list	*env_lst;
	t_list	*newlst;

	i = 0;
	env_lst = ft_lstnew(envp[i++]);
	while (envp[i])
	{
		newlst = ft_lstnew(envp[i]);
		ft_lstadd_back(&env_lst, newlst);
		i++;
	}
	return (env_lst);
}

int			env_builtin(char **args, int out)
{
	char	*cmd;
	char	*result;
	t_list	*tmp_lst;

	if (args[1] != NULL)
	{
		print("minishell: env: too many arguments\n", 2);
		return (1);
	}
	unset_builtin("_", "void");
	add_underscore("env");
	tmp_lst = g_env;
	cmd = ft_strdup(args[0]);
	result = ft_strdup("");
	while (tmp_lst->next)
	{
		result = ft_strjoin(ft_strjoin(result, tmp_lst->content), "\n");
		tmp_lst = tmp_lst->next;
	}
	result = ft_strjoin(result, tmp_lst->content);
	print(result, out);
	print("\n", out);
	ft_strdel(&cmd);
	ft_strdel(&result);
	return (0);
}
