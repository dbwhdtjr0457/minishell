/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:46:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/05 14:55:34 by jihylim          ###   ########.fr       */
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

char	*change_quote_dollar(t_token *token, t_list *env)
{
	char	*str;
	t_list	*token_list;

	// " " 잘라낸 부분 : str
	str = ft_substr(token->token, 1, ft_strlen(token->token) - 2);
	if (!str || !ft_strncmp(str, "\0", ft_strlen(str) + 1))
		return (0);
	token_list = make_token(str);
	free(str);
	token_list = change_to_env(token_list, env, 1);
	if (!token_list)
		return (0);
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
	if (!remove_d || !ft_strncmp(remove_d, "\0", ft_strlen(remove_d) + 1))
		res = ft_strdup("$");
	else if (get)
		res = ft_strdup(get);
	else
		res = 0;
	free(get);
	free(remove_d);
	return (res);
}

t_list	*del_token(t_list *pre, t_list *cur, t_list **lst)
{
	t_list	*del;

	del = cur;
	if (pre)
	{	
		pre->next = cur->next;
		cur = cur->next;
	}
	else
	{
		cur = cur->next;
		*lst = cur;
	}
	free(((t_token *)(del->content))->token);
	free(((t_token *)(del->content)));
	free(del);
	return (cur);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	while (s1 && s1[j])
		tmp[i++] = s1[j++];
	j = 0;
	while (s1 && s2[j])
		tmp[i++] = s2[j++];
	tmp[i] = '\0';
	free(s1);
	free(s2);
	return (tmp);
}

char	*change_env_type(t_token *token, t_list *env, int flag)
{
	char	*str;

	str = 0;
	if (token->type == QUOTE_DOUBLE || (token->type == QUOTE_SINGLE && flag))
	{	
		str = change_quote_dollar(token, env);
		if (token->type == QUOTE_SINGLE)
		{
			if (!str)
				str = ft_strdup("''");
			else
				str = ft_strjoin_free(ft_strdup("'"),
						ft_strjoin_free(str, ft_strdup("'")));
		}
	}
	else if (token->type == DOLLAR_T)
		str = change_dollar(token, env);
	else if (token->type == QUOTE_SINGLE)
	{
		str = ft_substr(token->token, 1, ft_strlen(token->token) - 2);
		token->type = WORD_T;
	}
	return (str);
}

// 환경변수 매칭 실패 시 토큰 없애기
// " " 제거 후 split 해서 앞뒤 연결하기
t_list	*change_to_env(t_list *lst, t_list *env, int flag)
{
	t_list	*cur;
	char	*str;
	t_token	*token;
	t_list	*pre;
	int		heredoc;

	cur = lst;
	pre = 0;
	heredoc = 0;
	while (cur)
	{
		token = (t_token *)(cur->content);
		if (token->type == QUOTE_DOUBLE || token->type == QUOTE_SINGLE
			|| (token->type == DOLLAR_T && !heredoc))
		{
			str = change_env_type(token, env, flag);
			if (!str || !ft_strncmp(str, "\0", ft_strlen(str) + 1))
			{
				cur = del_token(pre, cur, &lst);
				continue ;
			}
			cur->content = new_token(str, token->type);
			free_token(token);
		}
		else if (token->type == REDIR_LL)
		{
			if (cur->next && is_space(cur->next))
			{	
				pre = cur;
				cur = cur->next;
			}
			heredoc = 1;
		}
		else if (cur->next && (is_space(cur->next) || is_redir(cur->next)))
			heredoc = 0;
		pre = cur;
		cur = cur->next;
	}
	return (lst);
}
