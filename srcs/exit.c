#include "minishell.h"

void	exit_builtin(char **args)
{
	int	arg_status;

	arg_status = 0;
	if (args[1] != NULL)
	{
		printf("yoyow\n");
		arg_status = ft_atoi(args[1]) % 256;
		printf("les culs !\n");
		if (arg_status == 0
			&& ft_strcmp(args[1], "0") != 0
			&& ft_strcmp(args[1], "-0") != 0
			&& ft_strcmp(args[1], "+0") != 0)
		{
			print("minishell: exit: ", 2);
			print(args[1], 2);
			print(": numeric argument required\n", 2);
			exit(255);
		}
		if (args[2] != NULL)
		{
			print("minishell: exit: ", 2);
			print("too many arguments\n", 2);
			exit(1);
		}
		exit(arg_status);
	}
	exit(*((int*)getglobal(STATUS)));
}
