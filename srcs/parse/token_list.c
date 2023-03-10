/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:55:19 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/10 18:59:23 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// #include "../minishell.h"

t_token	*new_token(char *input, int type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->token = input;
	new->type = type;
	return (new);
}

void	lexer_quote(int *type, int start, int *i, int *arr)
{
	*i += 1;
	while (arr[*i] && arr[*i] != *type)
	{
		*i += 1;
		if (arr[*i] == *type)
			break ;
	}
	if (arr[*i] != *type)
	{
		*i = start;
		*type = WORD_T;
	}
}

void	lexer_dollar(int type, int *i, int *arr)
{
	while (arr[*i + 1] && arr[*i + 1] != type)
	{
		*i += 1;
		if (arr[*i] != WORD_T || arr[*i] == SPACE_T)
		{
			*i -= 1;
			break ;
		}
	}
}

t_token	*lexer_split(char *line, int *arr, int *i, int flag)
{
	int		start;
	int		type;

	start = *i;
	type = arr[(*i)];
	if (type == WORD_T || type == SPACE_T
		|| type == REDIR_LL || type == REDIR_RR)
	{
		*i += 1;
		while (arr[*i] == type)
			*i += 1;
		*i -= 1;
		if (type == SPACE_T && !flag)
			start = *i;
	}
	else if (type == QUOTE_DOUBLE || type == QUOTE_SINGLE)
		lexer_quote(&type, start, i, arr);
	else if (type == DOLLAR_T)
		lexer_dollar(type, i, arr);
	return (new_token(ft_substr(line, start, *i - start + 1), type));
}

void	make_token_list(t_list **split_word, char *line, int *arr, int flag)
{
	int		i;
	t_token	*word;

	i = 0;
	*split_word = 0;
	while (arr[i])
	{
		word = lexer_split(line, arr, &i, flag);
		ft_lstadd_back(split_word, ft_lstnew(word));
		i++;
	}
}
