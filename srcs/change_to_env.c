/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:46:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/27 01:20:48 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// token_list 받아서 하나씩 순회
// token_list->content 하나씩 보면서
// token_list->content->token 의 내용을 확인
// token 한글자씩 보는데

// quote_env
	// token type이 "" 일 경우, "" 떼고, 안의 내용 공백 또는 $로 나누기
	// change_dollar
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

char	*change_double_q(t_token *token, t_list *env)
{
	char	*str;
	t_list	*token_list;

	// " " 잘라낸 부분 : str
	str = ft_substr(token->token, 1, ft_strlen(token->token) - 2);
	if (!str || !ft_strncmp(str, "\0", 2))
	{
		printf("여긴가\n");
		return (0);
	}
	token_list = make_token(str);
	free(str);
	token_list = change_to_env(token_list, env);
	if (!token_list)
		return (0);
	printf("프린트해보기%s\n", (((t_token *)(token_list->content))->token));
	// 다시 합치기
	str = token_join(token_list);
	ft_lstclear_token(&token_list);
	return (str);
}

// change_dollar
	// token type이 dollar 일 경우 달러 다음에 오는 문자만 잘라서 확인

char	*change_dollar(t_token *token, t_list *env)
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
		res = 0;
	free(get);
	free(remove_d);
	return (res);
}

t_list	*del_token(t_list *pre, t_list *cur)
{
	t_list	*del;

	printf("here\n");
	del = cur;
	if (pre)
		pre->next = cur->next;
	cur = cur->next;
	// print_word_in_list(cur->content);
	free_token(del);
	print_word_in_list(cur->content);
	// free(((t_token *)(del->content))->token);
	// free(((t_token *)(del->content)));
	(void)del;
	printf("del fin\n");
	return (cur);
}

// 환경변수 매칭 실패 시 토큰 없애기
// " " 제거 후 split 해서 앞뒤 연결하기
t_list	*change_to_env(t_list *lst, t_list *env)
{
	t_list	*cur;
	char	*str;
	t_token	*token;
	t_list	*pre;

	cur = lst;
	pre = 0;
	while (lst && cur)
	{
		token = (t_token *)(cur->content);
		if (token->type == QUOTE_DOUBLE || token->type == DOLLAR_T
			|| token->type == QUOTE_SINGLE)
		{
			if (token->type == QUOTE_DOUBLE)
				str = change_double_q(token, env);
			else if (token->type == DOLLAR_T)
				str = change_dollar(token, env);
			else if (token->type == QUOTE_SINGLE)
			{
				str = ft_substr(token->token, 1, ft_strlen(token->token) - 2);
				token->type = WORD_T;
			}
			if (!str || !ft_strncmp(str, "\0", 2))
			{
				printf("delll\n");
				cur = del_token(pre, cur);
				print_word_in_list(cur->content);
				if (!cur)
					return (0);
				// free_token(token);
				// free(token);
				printf("del fffffin\n");
				continue ;
			}
			else
				cur->content = new_token(str, token->type);
			// if (!lst || !lst->content)
			// 	return (0);
		}
		pre = cur;
		cur = cur->next;
	}
	// if (lst)
	// {
	// 	if (lst->content)
	// 		return (lst);
	// }
	return (lst);
}
