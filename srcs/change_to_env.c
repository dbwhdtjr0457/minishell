/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:46:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/26 00:07:51 by jihylim          ###   ########.fr       */
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
	t_list	*lst;
	int		len;
	char	*res;
	int		index;

	len = 0;
	index = 0;
	lst = token_list;
	while (lst)
	{
		len += ft_strlen(((t_token *)lst->content)->token);
		lst = lst->next;
	}
	res = (char *)ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (0);
	lst = token_list;
	while (lst)
	{
		len = ft_strlen(((t_token *)lst->content)->token);
		ft_memcpy(res + index, ((t_token *)lst->content)->token, len);
		index += len;
		lst = lst->next;
	}
	return (res);
}

char	*quote_env(t_token *token, t_list *env)
{
	char	*str;
	t_list	*token_list;

	// " " 잘라낸 부분 : str
	str = ft_substr(token->token, 1, ft_strlen(token->token) - 2);
	token_list = make_token(str);
	free(str);
	token_list = change_to_env(token_list, env);
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
		res = ft_strdup("\0");
	free(get);
	free(remove_d);
	return (res);
}

// 환경변수 매칭 실패 시 토큰 없애기
// " " 제거 후 split 해서 앞뒤 연결하기

t_list	*change_to_env(t_list *token_list, t_list *env)
{
	t_list	*res;
	char	*str;
	t_token	*token;

	res = token_list;
	while (token_list)
	{
		token = (t_token *)((token_list)->content);
		if (token->type == QUOTE_DOUBLE)
		{
			// printf("%s\n", ((t_token*)make_token(quote_env(token, env))->next->next->content)->token);
			// ft_lstadd_back(&token_list, make_token(quote_env(token, env)));
			str = quote_env(token, env);
			token_list->content = new_token(str, QUOTE_DOUBLE);
			free_token(token);
		}
		else if (token->type == DALLOR_T || token->type == QUOTE_SINGLE)
		{
			if (token->type == DALLOR_T)
				str = change_dallor(token, env);
			else if (token->type == QUOTE_SINGLE)
				str = ft_substr(token->token, 1, ft_strlen(token->token) - 2);
			token_list->content = new_token(str, WORD_T);
			free_token(token);
		}
		token_list = token_list->next;
	}
	return (res);
}
