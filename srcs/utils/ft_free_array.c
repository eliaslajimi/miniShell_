#include "../minishell.h"

void		ft_free_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	while (i > 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}
	free(tab);
	tab = NULL;
}
