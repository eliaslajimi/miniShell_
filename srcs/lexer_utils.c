#include "minishell.h"

int		ft_isin(int c, char *set)
{
	while (set && *set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int		skip_spaces(char *line)
{
	int	i;
	i = 0;
	while (ft_isin(line[i], " \t\n\r\v\f"))
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*new_s;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	if (!(new_s = malloc((ft_strlen(s1) + 1) * sizeof(char))))
		return (NULL);
	while (s1 && *s1)
		new_s[i++] = *s1++;
	new_s[i] = '\0';
	return (new_s);
}

char	*ft_strndup(const char *s1, int n)
{
	char	*new_s;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	if (!(new_s = malloc((n < ft_strlen(s1) + 1 ? n : ft_strlen(s1)) * sizeof(char))))
		return (NULL);
	while (s1 && *s1 && n)
	{
		n--;
		new_s[i++] = *s1++;
	}
	new_s[i] = '\0';
	return (new_s);
}

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int		ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (1);
	}
	return (0);
}

void	ft_strdel(char **s)
{
	if (s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}

int		skip_quote(char *line, char quote, int i)
{
	int skip = i + 1;
	while (line[skip] && line[skip] != quote)
		skip++;
	if (line[skip] == quote)
		return (skip - i);
	return (0);
}
