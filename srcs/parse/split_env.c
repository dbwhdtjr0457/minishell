/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:32:41 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/10 19:04:08 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list	*token_add_back(t_list **lst, t_list **pre, t_list **res, t_list **new)
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
			new = make_token(((t_token *)lst->content)->token, 0);
			lst = token_add_back(&lst, &pre, &res, &new);
		}
		pre = lst;
		lst = lst->next;
	}
	return (res);
}
