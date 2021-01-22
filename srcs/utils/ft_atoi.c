#include "../minishell.h"

int						ft_atoi_minishell(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||\
			str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = 10 * result + str[i] - '0';
		i++;
	}
	result = result * sign;
	return ((int)result);
}
/*
int 				ft_atoi_shlvl(const char *str)
{
	int					i;
	int					sign;
	int					nb_signs;
	unsigned long long	result;

	i = 0;
	result = 0;
	sign = 1;
	nb_signs = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||\
			str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
	}
	while (str[i] == '-' || str[i] == '+')
	{
		i++;
		nb_signs++;
	}
	
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = 10 * result + str[i] - '0';
		if (result > LONG_MAX)
			return ((sign == -1) ? 0 : -1);
		i++;
	}
	if (result == 0)
	{
	//	printf("result == 0\n");
		return (0);
	}
	if (nb_signs > 1)
	{
	//	printf("nb_signs > 1\n");
		return (1);
	}
	if (sign == -1)
	{
	//	printf("case sign = -1\n");
		return (-1);
	}
	if (result > 2000000)
		return (-1);
	result = result * sign;
	return (result);
}
*/

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
			|| c == '\r' || c == ' ');
}

int			ft_atoi_shlvl(const char *nptr)
{
	int					moins;
	unsigned long long	nbr;

	moins = 1;
	nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*(nptr++) == '-')
			moins *= -1;
	}
	while (*nptr >= '0' && *nptr <= '9')
		nbr = (10 * nbr + (*(nptr++) - 48));
	if (nbr > LONG_MAX)
	{
		errno = ERANGE;
		return (0);
	}
	return ((int)(moins * nbr));
}