/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:01:32 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/09 08:07:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_texp(t_exp *t)
{
	t->i = 0;
	t->j = -1;
	t->k = -1;
	t->env_lst = g_env;
	t->found = NULL;
	t->newnode = NULL;
}

int			export_print_error(char *s1, char *s2, int s3)
{
	if (s1)
		print(s1, 2);
	if (s2)
		print(s2, 2);
	if (s3 == 1)
		print("': not a valid identifier\n", 2);
	return (1);
}

int			export_builtin2(t_exp *t, char *arg)
{
	if (ft_strcmp(t->split_arg[0], "SHLVL") == 0)
	{
		if (t->split_arg[1])
			export_shlvl(t->split_arg[1]);
		else
			export_shlvl("1");
		ft_free_array(t->split_arg);
		return (0);
	}
	while (t->split_arg[0][++t->j])
		if (ft_isin(t->split_arg[0][t->j], "\'\"\\$@!|;& "))
			return (export_print_error("minishell: export: `", arg, 1));
	t->found = ft_strdup(find_node(t->split_arg[0]));
	if (t->found != NULL)
		unset_builtin(t->split_arg[0], "void");
	free(t->found);
	ft_free_array(t->split_arg);
	while (arg[t->i] && arg[t->i] != '=')
		t->i++;
	if (t->i == 0)
		return (1);
	ft_lstadd_back(&(t->env_lst), ft_lstnew(arg));
	return (0);
}

int			export_builtin(char *arg, int out)
{
	t_exp	t;

	init_texp(&t);
	if (arg[0] == '\0')
	{
		return (export_print_error(
			"minishell: export: `': not a valid identifier\n", NULL, 0));
	}
	else if (ft_isin(arg[0], "0123456789="))
	{
		return (export_print_error(
			"minishell: export: `", arg, 1));
	}
	else if (ft_isin('=', arg))
	{
		t.split_arg = ft_split(arg, '=');
		return (export_builtin2(&t, arg));
	}
	else if (ft_strcmp(arg, "null") == 0)
		return (join_sorted_list(t.env_lst, out));
	else
	{
		while (arg && arg[++t.k])
			if (ft_isin(arg[t.k], "\'\"\\$@!|;& "))
			{
				write(1, "this is going through\n", ft_strlen("this is going through\n"));
				return (export_print_error(
					"minishell: export: `", arg, 1));
			}
	}
	return (0);
}
