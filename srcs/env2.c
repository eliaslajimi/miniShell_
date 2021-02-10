/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:05:31 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/09 08:01:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			add_underscore_main(void)
{
	t_list	*newnode;

	newnode = ft_lstnew("_=/bin/bash");
	ft_lstadd_back(&g_env, newnode);
	return (0);
}

int			add_underscore(char *cmd)
{
	char	*abs_path;
	t_list	*newnode;
	char	*underscore_env;

	abs_path = absolute_path(cmd);
	unset_builtin("_", "void");
	underscore_env = ft_strjoin(ft_strdup("_="), abs_path);
	newnode = ft_lstnew(underscore_env);
	ft_lstadd_back(&g_env, newnode);
	free(underscore_env);
	free(abs_path);
	return (0);
}

int			add_shlvl(void)
{
	t_list	*env_lst;
	t_list	*newnode;
	char	*found;

	env_lst = g_env;
	found = find_node("SHLVL");
	if (found == NULL)
	{
		newnode = ft_lstnew("SHLVL=1");
		ft_lstadd_back(&env_lst, newnode);
	}
	else
	{
		export_shlvl(cleannode(find_node("SHLVL")));
	}
	return (0);
}

int			add_oldpwd(void)
{
	char	*oldpwd;
	char	*oldpwd_env;

	if ((oldpwd = find_node("PWD")) != NULL)
	{
		oldpwd_env = ft_strdup("OLDPWD=");
		oldpwd = cleannode(oldpwd);
		oldpwd_env = ft_strjoin(oldpwd_env, oldpwd);
		export_builtin(oldpwd_env, 0);
		free(oldpwd_env);
	}
	return (0);
}

int			add_pwd(void)
{
	int		bufsize;
	char	*buf;
	char	*currentdir;
	char	*pwd_env;

	bufsize = 0;
	buf = NULL;
	pwd_env = ft_strdup("PWD=");
	add_oldpwd();
	currentdir = getcwd(buf, bufsize);
	pwd_env = ft_strjoin(pwd_env, currentdir);
	export_builtin(pwd_env, 0);
	free(pwd_env);
	free(currentdir);
	free(buf);
	return (0);
}
