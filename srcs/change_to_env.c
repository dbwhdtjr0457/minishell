/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:46:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/22 15:27:42 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// token_list 받아서 하나씩 순회
// token_list->content 하나씩 보면서
// token_list->content->token 의 내용을 확인
// token 한글자씩 보는데

// quote_env
	// token type이 "" 일 경우, "" 떼고, 안의 내용 공백 또는 $로 나누기
	// change_dallor
	// 치환 후 join으로 담기

char	*token_join(t_list *token_list)
{
	t_list	*list;
	int		len;
	char	*res;
	int		index;

	len = 0;
	index = 0;
	list = token_list;
	while (list)
	{
		len += ft_strlen(((t_token *)list->content)->token);
		list = list->next;
	}
	res = (char *)ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (0);
	list = token_list;
	while (list)
	{
		len = ft_strlen(((t_token *)list->content)->token);
		ft_memcpy(res + index, ((t_token *)list->content)->token, len);
		index += len;
		list = list->next;
	}
	return (res);
}

char	*quote_env(t_token *token, t_list *env)
{
	char	*str;
	int		*lexer_arr;
	t_list	*token_list;

	// " " 잘라낸 부분 : str
	str = ft_substr(token->token, 1, ft_strlen(token->token) - 2);
	lexer_arr = (int *)ft_calloc(ft_strlen(str) + 1, sizeof(int));
	lexer(str, lexer_arr);
	make_token_list(&token_list, str, lexer_arr);
	free(lexer_arr);
	free(str);
	token_list = change_to_env(&token_list, env);
	// 다시 합치기
	str = token_join(token_list);
	ft_lstclear_token(&token_list);
	return (str);
}

// change_dallor
	// token type이 dallor 일 경우 달러 다음에 오는 문자만 잘라서 확인

char	*change_dallor(t_token *token, t_list *env)
{
	char	*remove_d;
	char	*res;
	char	*get;

	res = 0;
	remove_d = ft_substr(token->token, 1, ft_strlen(token->token) - 1);
	get = get_env(remove_d, env);
	if (get)
		res = ft_strdup(get);
	else
		res = ft_strdup(token->token);
	free(get);
	free(remove_d);
	return (res);
}

t_list	*change_to_env(t_list **token_list, t_list *env)
{
	t_list	*res;
	char	*change;
	t_token	*token;

	res = *token_list;
	while (*token_list)
	{
		token = (t_token *)((*token_list)->content);
		if (token->type == DALLOR_T || token->type == QUOTE_DOUBLE)
		{
			if (token->type == QUOTE_DOUBLE)
				change = quote_env(token, env);
			else
				change = change_dallor(token, env);
			(*token_list)->content = new_token(change, WORD_T);
			free_token(token);
		}
		(*token_list) = (*token_list)->next;
	}
	return (res);
}
