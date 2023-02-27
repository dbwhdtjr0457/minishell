/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_comb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:50:47 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/28 00:29:57 by jihylim          ###   ########.fr       */
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

t_list	*comb_redir(t_list *lst, t_list **res)
{
	t_list	*cur;
	t_token	*token;
	char	*tmp;

	cur = lst->next;
	tmp = 0;
	while (cur)
	{
		token = (t_token *)(cur->content);
		if (token->type == SPACE_T)
			;
		else if (token->type == WORD_T)
		{
			tmp = ft_strdup(token->token);
			if (!tmp)
				return (0);
			ft_lstadd_back(res,
				ft_lstnew(new_token(tmp, ((t_token *)(lst->content))->type)));
			return (cur->next);
		}
		else if (token->type == PIPE_T)
			return (0);
		cur = cur->next;
	}
	return (0);
}

// 따옴표 제거하기
// token에 값이 \0 일 경우 제거하기
t_list	*split_quote(t_list *lst)
{
	t_list	*res;
	t_list	*tmp;
	t_list	*pre;
	t_list	*del;

	res = lst;
	pre = 0;
	while (lst && lst->content)
	{
		tmp = 0;
		// printf("list %sa\n", ((t_lst->content->)
		if (is_double(lst))
		{
			del = lst;
			tmp = make_token(((t_token *)lst->content)->token);
			if (pre)
				pre->next = tmp;
			else
				res = tmp;
			ft_lstlast(tmp)->next = lst->next;
			free_token(del->content);
			free(del);
			lst = tmp;
		}
		pre = lst;
		lst = lst->next;
	}
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
			//else if (is_pipe(lst))
			//	lst = comb_pipe(lst, &(res->parsed));
			else if (is_redir(lst))
			{
				printf("here%s\n",  ((t_token *)(lst->content))->token);
				lst = comb_redir(lst, &(mini->redir));

			}
			else
				append(&mini->parsed, ((t_token *)(lst->content))->token);
			if (!lst)
			{
				//free_mini(mini);
				ft_lstclear_mini(&res);
				return (0);
			}
			lst = lst->next;
		}
		ft_lstadd_back(&res, ft_lstnew(mini));
		if (lst && is_pipe(lst))
			lst = lst->next;
	}
	return (res);
}
