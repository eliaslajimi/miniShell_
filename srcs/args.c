#include "minishell.h"

static int		skip_quote_lexer(char *line, char quote)
{
	int skip;

	skip = 1;
	while (line[skip] && line[skip] != quote)
	{
		if (quote == '\"' && line[skip] == '\\')
		{
				skip += 2;
		}
		else
			skip++;
	}
	return (skip + 1);
}

static int	matching_quotes_args(char *line)
{
	int	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '\"' && line[i] != '\'' && line[i] != '\\')
			i++;
		if (line[i] == '\"')
		{
			i += skip_quote_lexer(line + i, '\"');
			if (i == ft_strlen(line) + 1)
			{
				return (-1);
			}
		}
		else if (line[i] == '\'')
		{
			i += skip_quote_lexer(line + i, '\'');
			if (i == ft_strlen(line) + 1)
			{
				return (-2);
			}
		}
		else if (line[i] == '\\')
		{
				i += 2;
		}
	}
	return (0);
}

void args(char **argv)
{
	int		start = 0;
	int		end;
	char	*inputcmd;
	char	*cmd;
	char	**tokens;
	c_table	**init, *ctable;

//	ctable = init;
	inputcmd = ft_strdup(argv[2]);
	if (matching_quotes_args(inputcmd) == -1)
	{
		print("minishell: unexpected EOF while looking for matching `\"\'\n",2);
		exit(2);
	}
	else if (matching_quotes_args(inputcmd) == -2)
	{
		print("minishell: unexpected EOF while looking for matching `\'\'\n",2);
		exit(2);
	}
	while (start < ft_strlen(inputcmd))
	{
		init = getstruct();
		*init = init_struct();
		ctable = *init;
		end = find_semic(inputcmd, start);
		cmd = ft_substr(inputcmd, start, end - start);
		start = end + 1;
		if (!(tokens = lexer(cmd)))
			wrapper(*init);
		parser(ctable, tokens);
		executor(init);
		free(tokens);
	}
/*		if ((tokens = lexer(input)) != NULL)
		{
			parser(ctable, tokens);
			executor(&init);	
			free(tokens);
		}
*/
	exitroutine(*init);
	exit(*(int*)getglobal(STATUS));
}
