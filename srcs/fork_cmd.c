/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:05:49 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 17:14:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**build_env_tab(void)
{
	int			i;
	int			lstsize;
	char		**env_tab;
	t_list		*envlst;

	i = 0;
	envlst = g_env;
	lstsize = ft_lstsize(envlst);
	if (!(env_tab = ft_calloc(lstsize + 1, sizeof(char *))))
		return (NULL);
	env_tab[lstsize] = NULL;
	while (i < lstsize)
	{
		env_tab[i] = ft_strdup(envlst->content);
		envlst = envlst->next;
		i++;
	}
	return (env_tab);
}

void			init_tfork(t_fork *t)
{
	t->status = (int*)getglobal(STATUS);
	t->env_tab = build_env_tab();
	t->sstdin = dup(0);
	t->sstdout = dup(1);
	t->pid = 0;
}

int				fork_cmd2(char **args, t_table *ctable, t_fork *t)
{
	if (ctable->out > 2)
		dup2(ctable->out, 1);
	if (ctable->in > 2)
		dup2(ctable->in, 0);
	errno = 0;
	*t->status = execve(args[0], &args[0], t->env_tab);
	if (errno != 0 && ft_strncmp(args[0], "./", 2))
	{
		p("minishell: ", args[0], ": ");
		print(strerror(errno), 2);
		print("\n", 2);
		return (126);
	}
	exit(*t->status);
	return (0);
}

int				fork_cmd(char *cmd, char **args, t_table *ctable)
{
	t_fork		t;

	init_tfork(&t);
	args[0] = ft_strdup(cmd);
	add_underscore(args[ctable->args_len - 1]);
	if (!ft_strlen(cmd))
		return (*t.status = 2);
	t.pid = fork();
	if (t.pid == 0)
	{
		if (fork_cmd2(args, ctable, &t) == 126)
			return (126);
	}
	else if (t.pid < 0)
		return (-1);
	waitpid(t.pid, t.status, 0);
	dup2(t.sstdin, 0);
	dup2(t.sstdout, 1);
	ft_free_array(t.env_tab);
	return (*t.status);
}
