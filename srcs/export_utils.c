/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:00:56 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/01/14 16:50:22 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void		iter_and_join2(t_iaj *t, char *booltab, t_list *env_lst)
{
	while (t->i < ft_lstsize(env_lst))
	{
		if (ft_strcmp(t->tmp, t->iter->content) >= 0 && booltab[t->i] == '1')
		{
			t->tmp = t->iter->content;
			t->j = t->i;
		}
		t->i++;
		t->iter = t->iter->next;
	}
}

static char		*iter_and_join(int nbfalse, char *booltab, t_list *env_lst)
{
	t_iaj		t;
	char		*other;
	while (--nbfalse >= 0)
	{
		char *declarex_str = ft_strdup("declare -x ");
		t.i = -1;
		t.j = 0;
		t.iter = env_lst;
		while (booltab[++t.i] == '0')
			t.iter = t.iter->next;
		t.tmp = t.iter->content;
		iter_and_join2(&t, booltab, env_lst);
		booltab[t.j] = '0';
		t.n = 0;
		while (t.tmp[t.n] != '=')
			t.n++;
		t.n++;
		other = ft_strndup(t.tmp, t.n);
        other = ft_strjoin(other, "\"");
        other = ft_strjoin(other, t.tmp + t.n);
        other = ft_strjoin(other, "\"");
        other = ft_strjoin(declarex_str, other);
        t.declarex_lst = ft_strjoin(t.declarex_lst, other);
        t.declarex_lst = ft_strjoin(t.declarex_lst, "\n");
		//t.declarex_lst = ft_strjoin(ft_strjoin(t.declarex_lst,
		//ft_strjoin(ft_strdup("declare -x "), ft_strjoin(ft_strjoin(
		//ft_strjoin(ft_strndup(t.tmp, t.n), "\""), t.tmp + t.n), "\""))), "\n");
	}
	free(booltab);
	return (t.declarex_lst);
}
*/

static char     *iter_and_join(int nbfalse, char *booltab, t_list *env_lst)
{
        int             i;
        int             j;
        t_list  *iter;
        char    *tmp;
        char    *declarex_lst;
        char    *declarex_str;

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

                int n = 0;
                char *other;
                while (tmp[n] != '=')
                        n++;
                n++;
                other = ft_strndup(tmp, n);
                other = ft_strjoin(other, "\"");
                other = ft_strjoin(other, tmp + n);
                other = ft_strjoin(other, "\"");
                other = ft_strjoin(declarex_str, other);
                declarex_lst = ft_strjoin(declarex_lst, other);
                declarex_lst = ft_strjoin(declarex_lst, "\n");
        }
        free(booltab);
        return (declarex_lst);
}

int				join_sorted_list(t_list *env_lst, int out)
{
	int			i;
	int			listsize;
	int			nbfalse;
	char		*booltab;

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
