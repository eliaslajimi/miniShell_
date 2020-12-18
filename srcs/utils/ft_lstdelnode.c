#include "../minishell.h"

int	 ft_lstdelnode(t_list **lst, char *data, int datalen)
{
	t_list	*current;
	t_list	*previous;

	previous = NULL;
	current = *lst;
	while (current)
	{
		if (ft_strncmp(current->content, data, datalen) == 0)
		{
			if (previous == NULL)
				*lst = current->next;
			else
				previous->next = current->next;
			free(current);
			return (1);
		}
		if (current->next == NULL)
			break;
		previous = current;
		current = current->next;
	}
	return (0);
}
