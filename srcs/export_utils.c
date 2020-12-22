#include "minishell.h"

static void	printit(char *tmp)
{
	write(1, "declare -x \"", 12);
	write(1, tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
	write(1, "\"\n", 2);
}

static void	iter_and_print(int nbfalse, char *booltab, t_list *env_lst)
{
	int	i;
	int	j;
	t_list	*iter;
	char	*tmp;

	while (--nbfalse >= 0)
	{
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
		printit(tmp);
	}
}

int			print_sorted_list(t_list *env_lst)
{
	int		i;
	int		listsize;
	int		nbfalse;
	char	*booltab;
	t_list	*iter;

	i = 0;
	listsize = ft_lstsize(env_lst);
	booltab = ft_calloc(listsize, 1);
	iter = env_lst;
	while (i++ < listsize)
		booltab[i] = '1';
	nbfalse = listsize;
	iter_and_print(nbfalse, booltab, env_lst);
	return (0);
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
