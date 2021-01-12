/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:00:56 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/01/12 10:02:38 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*iter_and_join(int nbfalse, char *booltab, t_list *env_lst)
{
	int		i;
	int		j;
	t_list	*iter;
	char	*tmp;
	char	*declarex_lst;
	char	*declarex_str;
	
	declarex_lst = ft_strdup("");
	while (--nbfalse >= 0)
	{
		declarex_str = ft_strdup("declare -x ");
		i = -1;
		j = 0;
		iter = env_lst;
		while (booltab[++i] == '0')
			iter = iter->next;
		tmp = iter->content;
		while (i < ft_lstsize(env_lst))
		{
			if (ft_strcmp(tmp, iter->content) >= 0 && booltab[i] == '1')
			{
				tmp = iter->content;
				j = i;
			}
			i++;
			iter = iter->next;
		}
		booltab[j] = '0';
		tmp = ft_strjoin(declarex_str, tmp);
		declarex_lst = ft_strjoin(declarex_lst, tmp);	
		declarex_lst = ft_strjoin(declarex_lst, "\n");
	}
	free(booltab);
	return (declarex_lst);
}

int			join_sorted_list(t_list *env_lst, int out)
{
	int		i;
	int		listsize;
	int		nbfalse;
	char	*booltab;

	i = 0;
	listsize = ft_lstsize(env_lst);
	if (!(booltab = ft_calloc(listsize + 1, 1)))
	{
		print("calloc error", 2);
		return (1);
	}
	while (i++ < listsize)
		booltab[i] = '1';
	nbfalse = listsize;
	print(iter_and_join(nbfalse, booltab, env_lst), out);
	return (0);
}
