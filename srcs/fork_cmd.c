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

static char	**build_env_tab()
{
	int		i;
	int		lstsize;
	char	**env_tab;
	t_list	*envlst;

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

int fork_cmd(char *cmd, char **args, t_table *ctable)
{
	pid_t	pid;
	char	**env_tab;
	int	*status;
	int sstdin, sstdout;

	status = (int*)getglobal(STATUS);
	env_tab = build_env_tab();

	sstdin = dup(0);
	sstdout = dup(1);
	args[0] = ft_strdup(cmd);
	pid = 0;
	(void)cmd;
	
	add_underscore(args[ctable->args_len-1]);

	if (!ft_strlen(cmd))
	{
		*status = 2;
		return (*status);	
	}
	pid = fork();
	if (pid == 0)//CHILD
	{
		if (ctable->out > 2)
			dup2(ctable->out, 1);
		if (ctable->in > 2)
			dup2(ctable->in, 0);
		errno = 0;
		*status = execve(args[0], &args[0], env_tab);
		if (errno != 0 && ft_strncmp(args[0], "./", 2))
		{
			print("minishell: ", 2);
			print(args[0], 2);
			print(": ", 2);
			print(strerror(errno), 2);
			print("\n", 2);
			return (126);
		}
		exit(*status);
	}
	else if (pid < 0)
	{
		return (-1);
	}
	waitpid(pid, status, 0);
	dup2(sstdin, 0);
	dup2(sstdout, 1);
	ft_free_array(env_tab);
	return (*status);
}
