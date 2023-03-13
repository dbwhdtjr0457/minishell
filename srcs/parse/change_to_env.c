/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:46:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/13 16:26:34 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	next_lst(t_list **pre, t_list **cur)
{
	*pre = *cur;
	*cur = (*cur)->next;
}

static int	change_env_quo(t_list **pre, t_list **cur, t_list **lst, char *str)
{
	t_token	*token;

	token = (t_token *)((*cur)->content);
	if (!str || !ft_strncmp(str, "\0", ft_strlen(str) + 1))
	{
		*cur = token_del(*pre, *cur, lst);
		return (0);
	}
	(*cur)->content = new_token(str, token->type);
	free_token(token);
	return (1);
}

// 환경변수 매칭 실패 시 토큰 없애기
// " " 제거 후 split 해서 앞뒤 연결하기
t_list	*change_to_env(t_list *lst, t_list *env, int flag)
{
	t_list	*pre;
	t_list	*cur;
	int		heredoc;

	pre = 0;
	cur = lst;
	heredoc = 0;
	while (cur)
	{
		if (is_double(cur) || is_single(cur) || (is_dollar(cur) && !heredoc))
		{
			if (!change_env_quo(&pre, &cur, &lst, remove_quote(cur, env, flag)))
				continue ;
		}
		else if (((t_token *)(cur->content))->type == REDIR_LL)
		{
			if (cur->next && is_space(cur->next))
				next_lst(&pre, &cur);
			heredoc = 1;
		}
		else if (cur->next && (is_space(cur->next) || is_redir(cur->next)))
			heredoc = 0;
		next_lst(&pre, &cur);
	}
	return (lst);
}
