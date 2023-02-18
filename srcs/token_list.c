/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:55:19 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/18 17:03:01 by jihylim          ###   ########.fr       */
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
	type = arr[*i];
	if (arr[*i] == WORD_TOKEN || arr[*i] == SPACE_TOKEN
		|| arr[*i] == REDIR_LL || arr[*i] == REDIR_RR)
	{
		while (arr[*i] == type)
			*i += 1;
		*i -= 1;
	}
	else if (arr[*i] == QUOTE_DOUBLE || arr[*i] == QUOTE_SINGLE)
	{
		*i += 1;
		while (arr[*i] && arr[*i] != type)
		{
			*i += 1;
			if (arr[*i] == type)
				break ;
		}
	}
	return (new_token(ft_substr(line, start, *i - start + 1), type));
}

void	token_list(t_list **split_word, char *line, int *arr)
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
