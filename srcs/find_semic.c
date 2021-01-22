#include "minishell.h"
#include <string.h>

int		find_semic(char *line, int start)
{
	int i = start;
	
		//printf("line find semic [%s]\n", line);

	while (line[i] && line[i] != ';')
	{
		//printf("line[i] is [%c]\n", line[i]);
		if (line[i] == '\\')
		{
			i += 2;
		}
		else if (line[i] == '\"')
		{
			i++;
			if (line[i] == '\\')
			{
				i += 2;
			}
			while (line[i] != '\"')
			{
				if (line[i] == '\\')
					i += 2;
				if (line[i])
					i++;
				else
					break;
			}
			if (line[i])
				i++;
		}
		else if (line[i] == '\'')
		{
			//printf("sq on line +i [%s]", line + i);	
			i++;
			while (line[i] != '\'')
				i++;
			i++;
		}
		else
		{
		//printf("we just increment [%s]\n", line + i);
			i++;

		}
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
