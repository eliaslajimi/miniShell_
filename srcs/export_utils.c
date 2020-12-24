#include "minishell.h"

static char	*iter_and_join(int nbfalse, char *booltab, t_list *env_lst)
{
	int		i;
	int		j;
	t_list	*iter;
	char	*tmp;
	char	*declarex_lst;
	char	*wtfallocthis;
	
	while (--nbfalse >= 0)
	{
		wtfallocthis = ft_strdup("declare -x "); // a proteger
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
		tmp = ft_strjoin(wtfallocthis, tmp);
		declarex_lst = ft_strjoin(declarex_lst, tmp);
		declarex_lst = ft_strjoin(declarex_lst, "\n");
	}
	return (declarex_lst);
}

int			join_sorted_list(t_list *env_lst)
{
	int		i;
	int		listsize;
	int		nbfalse;
	char	*booltab;

	i = 0;
	listsize = ft_lstsize(env_lst);
	if (!(booltab = ft_calloc(listsize, 1)))
	{
		print("calloc error", 1);
		return (1);
	}
	while (i++ < listsize)
		booltab[i] = '1';
	nbfalse = listsize;
	print(iter_and_join(nbfalse, booltab, env_lst), 1);
	return (0); //0 quand ca a marché
}

char	*find_node(t_list **lst, char *data)
{
	t_list	*iter;

	iter = *lst;
	while (iter)
	{
		if (ft_strncmp(iter->content, data, ft_strlen(data)) != 0)
		{
			return (iter->content);
		}
		else if (iter->next == NULL)
		{
			break;
		}
		iter = iter->next;
	}
	return (NULL);
}
