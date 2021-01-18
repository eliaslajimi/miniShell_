#include "minishell.h"
#include <string.h>

int		find_semic(char *line, int start)
{
	int i = start;
	
	while (line [i] && line[i] != ';')
	{
		if (line[i] == '\\')
			i += 2;
		else if (line[i] == '\"')
		{
			i++;
			if (line[i] == '\\')
				i += 2;
			while (line[i] != '\"')
			{
				if (line[i] == '\\')
					i += 2;
				i++;
			}
			i++;
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
			i++;
		}
		else
			i++;
	}
	return (i);
}
/*
int main(int argc, char **argv)
{
	int start = 0;
	int end;
	char *result;
	char *test = strdup(argv[1]);
	while (start < strlen(test))
	{
		end = find_semic(test, start);
		result = ft_substr(test, start, end - start);
		start = end + 1;
		printf("%s\n", result);
		free(result);
	}
	return (0);
}*/
