#include "minishell.h"

//void **getglobal(int mode, void **value)
//{
//	static void	**ret;
//	static void	**ret_status;
//	static void	**ret_struct;
//	
//	if (mode == STRUCT)
//	{
//		if (value)
//			ret_struct = value;
//		ret = ret_struct;
//	}
//	if (mode == STATUS)
//	{
//		if (value)
//			ret_status = value;
//		ret = ret_status;
//	}
//	return (ret);
//}

void *getglobal(int mode)
{
	static c_table *ret_struct;
	static int *ret_status;
	
	if (mode == STRUCT)
		return ((void*)&ret_struct);
	if (mode == STATUS)
		return ((void*)&ret_status);
	return (NULL);
}

void exitroutine()
{
	c_table *init;

	init = (c_table*)getglobal(STRUCT);	
	while (init)
		next_struct(&init);
}

void	sighandler(int num)
{
	if (num == SIGQUIT)
	{
		exitroutine();	
		exit(*((int*)getglobal(STATUS)));
	}
	if (num == SIGINT)
	{
		exitroutine();	
		minishell();
	}
}

int	main(int argc, char **argv, char **envp)
{
	g_env = setEnv(envp);
	if (argc > 1)
		args(argv);	
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	minishell();
	return (0);
}
