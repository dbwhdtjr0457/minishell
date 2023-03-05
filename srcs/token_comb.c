/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_comb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:50:47 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/05 15:05:43 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_split	*new_split(char **input, int type)
{
	t_split	*new;

	new = (t_split *)malloc(sizeof(t_split));
	if (!new)
		return (0);
	new->split = input;
	new->type = type;
	return (new);
}

// char ** 형에 char * 추가해주는 함수
// res = {"hello"}가 있으면 res = {"hello", "world"} 처럼 뒤에 연결
void	append(char ***res, char *str)
{
	int		len;
	int		i;
	char	**tmp;
	char	**new;

	len = 0;
	i = -1;
	tmp = *res;
	if (tmp)
	{
		while (tmp[len])
			len++;
	}
	new = malloc((len + 2) * sizeof(char *));
	while (++i < len)
		new[i] = strdup(tmp[i]);
	new[len] = strdup(str);
	new[len + 1] = 0;
	i = 0;
	while (i < len)
		free(tmp[i++]);
	free(tmp);
	*res = new;
}

t_list	*comb_pipe(t_list *lst, t_list **res)
{
	t_split	*split;

	split = new_split(
			ft_split(((t_token *)(lst->content))->token, ' '),
			(((t_token *)(lst->content))->type));
	ft_lstadd_back(res, ft_lstnew(split));
	return (lst);
}

int	comb_redir(t_list **lst, t_list **res)
{
	t_list	*cur;
	t_token	*token;
	char	*tmp;

	cur = (*lst)->next;
	while (cur)
	{
		tmp = 0;
		token = (t_token *)(cur->content);
		if (token->type == SPACE_T)
			;
		else if (!is_space(cur) && !is_pipe(cur) && !is_redir(cur))
		{
			tmp = ft_strdup(token->token);
			if (!tmp)
				return (0);
			ft_lstadd_back(res, ft_lstnew
				(new_token(tmp, ((t_token *)((*lst)->content))->type)));
			(*lst) = cur;
			return (1);
		}
		else if (token->type == PIPE_T || is_redir(cur))
		{
			print_syn_error(cur, 0);
			return (0);
		}
		cur = cur->next;
	}
	print_syn_error(0, "'newline'\n");
	return (0);
}

t_list	*quote_join_if(t_list *cur, t_list **res, t_list **new)
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

t_list	*add_back(t_list **lst, t_list **pre, t_list **res, t_list **new)
{
	t_list	*del;

	del = *lst;
	if (*pre)
		(*pre)->next = *new;
	else
		*res = *new;
	ft_lstlast(*new)->next = (*lst)->next;
	free_token(del->content);
	free(del);
	return (*new);
}

t_list	*split_env(t_list *lst)
{
	t_list	*res;
	t_list	*new;
	t_list	*pre;

	res = lst;
	pre = 0;
	while (lst)
	{
		new = 0;
		if (is_dollar(lst)
			&& ft_strchr(((t_token *)(lst->content))->token, ' '))
		{
			new = make_token(((t_token *)lst->content)->token);
			lst = add_back(&lst, &pre, &res, &new);
		}
		pre = lst;
		lst = lst->next;
	}
	return (res);
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
	cur = lst;
	res = 0;
	while (cur && cur->content)
	{
		new = 0;
		while (cur && !is_space(cur) && !is_redir(cur) && !is_pipe(cur))
		{
			ft_lstadd_back(&new, ft_lstnew(
					new_token(ft_strdup(((t_token *)(cur->content))->token),
						((t_token *)(cur->content))->type)));
			cur = cur->next;
		}
		cur = quote_join_if(cur, &res, &new);
	}
	ft_lstclear_token(&lst);
	return (res);
}

// 연관있는 토큰끼리 합쳐주는 함수
// t_list *res의 content에 t_split 형태로 저장한 후 반환
// 인자로 받아온 token_list 는 free해줘야 함
t_list	*token_comb(t_list *lst)
{
	t_mini	*mini;
	t_list	*res;

	res = 0;
	while (lst)
	{
		mini = (t_mini *)malloc(sizeof(t_mini));
		mini->parsed = 0;
		mini->redir = 0;
		while (lst && !is_pipe(lst))
		{
			if (is_space(lst))
				;
			else if (is_redir(lst))
			{
				if (!comb_redir(&lst, &(mini->redir)))
				{
					free_mini(mini);
					ft_lstclear_mini(&res);
					return (0);
				}
			}
			else
				append(&mini->parsed, ((t_token *)(lst->content))->token);
			lst = lst->next;
		}
		ft_lstadd_back(&res, ft_lstnew(mini));
		if (lst && is_pipe(lst))
			lst = lst->next;
	}
	return (res);
}
