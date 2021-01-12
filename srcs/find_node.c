#include "minishell.h"

char *cleannode(char *node)
{
	if (!node)
		return (NULL);
	while(*node && *node != '=')
		++node;
	return (++node);
}

char	*find_node(char *data)
{
	t_list	*iter;
	char	**split_content;

	iter = g_env;
	while (iter && iter->next)
	{
		split_content = ft_split(iter->content, '=');
		if (ft_strcmp(split_content[0], data) == 0)
		{
			ft_free_array(split_content);
			return (iter->content);
		}
		else if (iter->next == NULL)
		{
			ft_free_array(split_content);
			break;
		}
		ft_free_array(split_content);
		iter = iter->next;
	}
	return (NULL);
}
