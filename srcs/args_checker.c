/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:57:25 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/11 15:43:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		checking_pipes(char *inputcmd)
{
	int			i;
	int			flag;

	i = 0;
	flag = 0;
	i += skip_spaces(inputcmd);
	if (inputcmd[i] == '|')
		return (-1);
	while (inputcmd[i])
	{
		i += skip_spaces(inputcmd + i);
		if (!(inputcmd[i]))
			break ;
		if (inputcmd[i] == '|' && flag == 0)
			flag = 1;
		else if (inputcmd[i] == '|' && flag == 1)
			return (-1);
		else
			flag = 0;
		i++;
	}
	if (flag == 1)
		return (-1);
	return (0);
}

int		checking_semic(char *inputcmd)
{
	int			i;
	int			flag;

	i = 0;
	flag = 0;
	i += skip_spaces(inputcmd);
	if (inputcmd[i] == ';')
		return (-1);
	while (inputcmd[i])
	{
		i += skip_spaces(inputcmd + i);
		if (inputcmd[i] == ';' && flag == 0)
			flag = 1;
		else if (inputcmd[i] == ';' && flag == 1)
			return (-1);
		else
			flag = 0;
		i++;
	}
	return (0);
}

int		skip_quote_lexer(char *line, char quote)
{
	int skip;

	skip = 1;
	while (line[skip] && line[skip] != quote)
	{
		if (quote == '\"' && line[skip] == '\\')
			skip += 2;
		else
			skip++;
	}
	return (skip + 1);
}

int		matching_quotes_args(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '\"' && line[i] != '\'' && line[i] != '\\')
			i++;
		if (line[i] == '\"')
		{
			i += skip_quote_lexer(line + i, '\"');
			if (i == ft_strlen(line) + 1)
				return (-1);
		}
		else if (line[i] == '\'')
		{
			i += skip_quote_lexer(line + i, '\'');
			if (i == ft_strlen(line) + 1)
				return (-2);
		}
		else if (line[i] == '\\')
		{
			i += 2;
		}
	}
	return (0);
}

int		args_checker(char *inputcmd)
{
	int	lexer_check_status;

	lexer_check_status = 0;
	if ((lexer_check_status = matching_quotes_args(inputcmd)) == -1)
		print("minishell: unexpected EOF while looking for matching
		`\"\'\n", 2);
	else if ((lexer_check_status = matching_quotes_args(inputcmd)) == -2)
		print("minishell: unexpected EOF while looking for matching
		`\'\'\n", 2);
	else if ((lexer_check_status = checking_semic(inputcmd)) == -1)
		print("minishell: syntax error near unexpected token `;'\n", 2);
	else if ((lexer_check_status = checking_pipes(inputcmd)) == -1)
		print("minishell: syntax error near unexpected token `|'\n", 2);
	if (lexer_check_status != 0)
		final_exit(2);
	lexer_check_status = lexer_special(inputcmd);
	if (lexer_check_status != 0)
		final_exit(lexer_check_status);
	return (0);
}
