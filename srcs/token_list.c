/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:55:19 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/19 20:06:02 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_token	*split_space_quote(char *line, int *arr, int *i)
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
	}
	else if (type == QUOTE_DOUBLE || type == QUOTE_SINGLE)
	{
		*i += 1;
		while (arr[*i] && arr[*i] != type)
		{
			*i += 1;
			if (arr[*i] == type)
				break ;
		}
	}
	else if (type == DALLOR_T)
	{
		*i += 1;
		while (arr[*i] && arr[*i] != type)
		{
			*i += 1;
			if (arr[*i] != WORD_T)
			{
				*i -= 1;
				break ;
			}
		}
	}

	// 달러가 나오면, 문자가 끝날때나(space 등 다른 토큰이 나올 때) 다른 달러 나올떄까지 받아서 저장
	// 달러 토큰 추가
	// 나중에 - 리스트 순회하다가 달러 토큰 나온것만 치환
	// env 에 없는 환경변수일 경우에는 리스트 없애기000
	return (new_token(ft_substr(line, start, *i - start + 1), type));
}

void	make_token_list(t_list **split_word, char *line, int *arr)
{
	int		i;
	t_token	*word;

	i = 0;
	*split_word = 0;
	while (arr[i])
	{
		word = split_space_quote(line, arr, &i);
		ft_lstadd_back(split_word, ft_lstnew(word));
		i++;
	}
}
