#include "minishell.h"

char	**lexer(char *inputcmd)
{
	char **tokens;
	
	tokens = ft_split(inputcmd, ' ');
	return (tokens);
}

