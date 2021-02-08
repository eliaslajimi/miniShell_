/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:01:27 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 14:01:28 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		shlvl_err_msg(int shlvl)
{
	write(1, "minishell: warning: shell level (",
		ft_strlen("minishell: warning: shell level ("));
	ft_putnbr_fd(shlvl, STDERR_FILENO);
	ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
}

int				export_shlvl(char *nb)
{
	char		*itoa_shlvl;
	t_list		*newnode;
	int			shlvl;
	char		*toexport;

	shlvl = (int)ft_atoi_shlvl(nb);
	shlvl++;
	(shlvl < 0) ? shlvl = 0 : shlvl;
	if (shlvl > 1000)
	{
		if (shlvl < INT_MAX)
			shlvl_err_msg(shlvl);
		shlvl = 1;
	}
	toexport = ft_strdup("SHLVL=");
	itoa_shlvl = ft_itoa(shlvl);
	toexport = ft_strjoin(toexport, itoa_shlvl);
	free(itoa_shlvl);
	if (find_node("SHLVL") != NULL)
		unset_builtin("SHLVL", "void");
	newnode = ft_lstnew(toexport);
	ft_lstadd_back(&g_env, newnode);
	free(toexport);
	return (0);
}

int				export_builtin_loop(char **arg, int args_len, int out)
{
	int			i;
	int			ret;
	char		*underscore;

	ret = 0;
	i = 1;
	arg++;
	while (i < args_len)
	{
		ret = export_builtin(*arg, out);
		arg++;
		i++;
	}
	arg--;
	i = 0;
	while ((*arg)[i] && (*arg)[i] != '=')
		i++;
	underscore = ft_strndup(*arg, i);
	add_underscore(underscore);
	free(underscore);
	if (args_len == 1)
		export_builtin("null", out);
	return (ret);
}
