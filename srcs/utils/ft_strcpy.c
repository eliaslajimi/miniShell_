#include "../minishell.h"

void		ft_strcpy(char *dst, char *src, int n)
{
	int	i;

	if (!(dst || src))
		return ;
	i = 0;
	while (src[i] && n > 0)
	{
		dst[i] = src[i];
		i++;
		n--;
	}
	dst[i] = '\0';
}
