#include "../minishell.h"

int		skip_spaces(char *line)
{
	int	i;
	i = 0;
	if (line)
	{
		while (ft_isin(line[i], " \t\n\r\v\f"))
			i++;
	}
	return (i);
}
