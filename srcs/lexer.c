/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:13:45 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/18 16:45:35 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//void	print_arr(char *arr)
//{
//	int	i;

//	i = 0;
//	while (arr[i])
//	{
//		printf("%d ", arr[i]);
//		i++;
//	}
//	printf("\n");
//}

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
			arr[i] = PIPE_TOKEN;
		else if (line[i] == ' ')
			arr[i] = SPACE_TOKEN;
		else
			arr[i] = WORD_TOKEN;
		i++;
	}
}