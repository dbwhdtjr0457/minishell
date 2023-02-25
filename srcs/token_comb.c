/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_comb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:50:47 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/25 21:56:18 by jihylim          ###   ########.fr       */
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

t_list	*comb_redir(t_list *lst, t_list **res)
{
	t_split	*split;
	char	**tmp;

	tmp = 0;
	if ((lst->next) && (is_word(lst->next) || (is_space(lst->next)
				&& (lst->next->next) && is_word(lst->next->next))))
	{
		append(&tmp, ((t_token *)(lst->content))->token);
		if (is_space(lst->next))
			lst = lst->next;
		append(&tmp, ((t_token *)(lst->next->content))->token);
		split = new_split(tmp, ((t_token *)(lst->content))->type);
		ft_lstadd_back(res, ft_lstnew(split));
		lst = lst->next;
	}
	else
	{	
		printf("redir error\n");
		return (0);
	}
	// else 리다이렉션 뒤에 word token이 나오지 않을 경우 에러 처리 필요 또는 리다이렉션만 나올경우(뒤에가 널일 경우)
	return (lst);
}

t_list	*comb_word(t_list *lst, t_list **res)
{
	t_split	*split;
	char	**tmp;
	char	*join;
	int		i;

	tmp = 0;
	i = 0;
	append(&tmp, ((t_token *)(lst->content))->token);
	while (((t_token *)(lst->next))
		&& (is_word(lst->next) || is_space(lst->next)))
	{
		lst = lst->next;
		if (lst && is_space(lst) && lst->next
			&& !is_pipe(lst->next) && !is_redir(lst->next))
		{
			lst = lst->next;
			append(&tmp, ((t_token *)(lst->content))->token);
			i++;
		}
		else if (lst && !is_space(lst))
		{	
			join = ft_strjoin(tmp[i], ((t_token *)(lst->content))->token);
			free(tmp[i]);
			tmp[i] = join;
		}
	}
	split = new_split(tmp, WORD_T);
	ft_lstadd_back(res, ft_lstnew(split));
	return (lst);
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
	while (lst)
	{
		tmp = 0;
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
	t_list	*res;
	t_list	*tmp;
	t_split	*split;

	res = 0;
	while (lst)
	{
		tmp = 0;
		if (is_space(lst))
			;
		else if (is_pipe(lst))
		{
			// pipe 뒤에 단어만 와야하나?? redir 와도 되는건가??
			// 지금은 단어만 와야하는 것/
			if (!res || !((lst->next) && (is_word(lst->next)
						|| (is_space(lst->next) && (lst->next->next)
							&& is_word(lst->next->next)))))
			{
				printf("pipe error\n");
				ft_lstclear_parsed(&res);
				// 바로 리턴 말고 프리 해주고 끝내야 함
				return (0);
			}
			split = new_split(
					ft_split(((t_token *)(lst->content))->token, ' '),
					(((t_token *)(lst->content))->type));
			ft_lstadd_back(&res, ft_lstnew(split));
		}
		else if (is_redir(lst))
			lst = comb_redir(lst, &res);
		else
			lst = comb_word(lst, &res);
		//system("leaks --list minishell");
		if (!lst)
		{
			ft_lstclear_token(&tmp);
			ft_lstclear_parsed(&res);
			return (0);
		}
		lst = lst->next;
		//if (tmp && tmp->content)
		//	ft_lstclear_token(&tmp);
		//system("leaks --list minishell");
	}
	//if (tmp && tmp->content)
	//		ft_lstclear_token(&tmp);
	//system("leaks --list minishell");
	return (res);
}
