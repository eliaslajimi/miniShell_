#include "minishell.h"

static int	check_extremes(char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	result = 0;
	sign = 0;
	if (ft_strcmp(str, "18446744073709551616") == 0)
		return (0);
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
	if (sign == -1)
	{
		if (result == 9223372036854775808UL)
			return (1);
	}
	if (result >= 9223372036854775808UL)
	{
		return (0);
	}
	return (1);
}


static int	check_arg(char *str)
{
	int i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||\
			str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	if (check_extremes(str) == 0)
		return (0);
	return (1);
}

void	final_exit(int status)
{
	ft_lstfree(g_env);
	exit(status);
}

void	exit_builtin(char **args)
{
	int	arg_status;

	arg_status = 0;
	if (args[1] != NULL)
	{
		if (check_arg(args[1]) == 0)
		{
			print("minishell: exit: ", 2);
			print(args[1], 2);
			print(": numeric argument required\n", 2);
			final_exit(255);
		}
		arg_status = ft_atoi_minishell(args[1]) % 256;
		if (args[2] != NULL)
		{
			print("minishell: exit: ", 2);
			print("too many arguments\n", 2);
			final_exit(1);
		}
		final_exit(arg_status);
	}
	final_exit(*((int*)getglobal(STATUS)));
}
