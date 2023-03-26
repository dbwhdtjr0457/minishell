/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:28:04 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/22 12:26:43 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_list	*quote_join_if(t_list *cur, t_list **res, t_list **new)
{
	t_token	*token;

	if (*new)
	{
		token = new_token(token_join(*new),
				((t_token *)((*new)->content))->type);
		ft_lstclear_token(new);
		ft_lstadd_back(res, ft_lstnew(token));
	}
	else
	{
		ft_lstadd_back(res, ft_lstnew(
				new_token(ft_strdup(((t_token *)(cur->content))->token),
					((t_token *)(cur->content))->type)));
		cur = cur->next;
	}
	return (cur);
}

void	ft_lstadd_back_token(t_list **lst, t_list **new)
{
	ft_lstadd_back(lst, ft_lstnew(
			new_token(ft_strdup(((t_token *)((*new)->content))->token),
				((t_token *)((*new)->content))->type)));
	*new = (*new)->next;
}

int	is_del_dollar(t_list *cur)
{
	if (is_dollar(cur) && ft_strchr(((t_token *)cur->content)->token, '$'))
		return (1);
	return (0);
}

// 리스트 하나씩 돌기
// 스페이스 아니면 새로운 토큰 만들어서 추가 => 이 새로운 토큰은 기존 토큰 재사용 X 아예 새로운 친구
// 추가하면서 원래 있던 토큰 지우기
// while 나와서 token_join 해서 하나의 str로 만들기
// 스페이스 지워서 담은 토큰리스트 지우고
// 이전 토큰 리스트위치에 넣기
t_list	*quote_join(t_list *lst)
{
	t_list	*cur;
	t_list	*res;
	t_list	*new;

	lst = split_env(lst);
	if (!lst)
		return (0);
	cur = lst;
	res = 0;
	while (cur && cur->content)
	{
		new = 0;
		while (cur && !is_space(cur) && !is_redir(cur) && !is_pipe(cur))
		{
			if (is_del_dollar(cur) && cur->next && is_quote(cur->next))
			{
				cur = cur->next;
				continue ;
			}
			ft_lstadd_back_token(&new, &cur);
		}
		cur = quote_join_if(cur, &res, &new);
	}
	ft_lstclear_token(&lst);
	return (res);
}
