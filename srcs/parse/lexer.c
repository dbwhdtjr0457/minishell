/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:13:45 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/08 19:55:20 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// #include "../minishell.h"

void	rexer_redir_check(const char *line, int *arr, int *i, int type)
{
	char	t;

	if (type == REDIR_L)
		t = '<';
	else
		t = '>';
	arr[*i] = type;
	if (line[*i + 1] && line[*i + 1] == t)
	{
		arr[*i] = type - 1;
		arr[*i + 1] = type - 1;
		(*i)++;
	}
}

void	lexer(const char *line, int *arr)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			arr[i] = QUOTE_DOUBLE;
		else if (line[i] == '\'')
			arr[i] = QUOTE_SINGLE;
		else if (line[i] == '<')
			rexer_redir_check(line, arr, &i, REDIR_L);
		else if (line[i] == '>')
			rexer_redir_check(line, arr, &i, REDIR_R);
		else if (line[i] == '|')
			arr[i] = PIPE_T;
		else if (line[i] == ' ')
			arr[i] = SPACE_T;
		else if (line[i] == '$')
			arr[i] = DOLLAR_T;
		else
			arr[i] = WORD_T;
		i++;
	}
}
