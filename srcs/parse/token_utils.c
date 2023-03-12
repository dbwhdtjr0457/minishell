/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:16:28 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/12 23:54:58 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_list	*token_del(t_list *pre, t_list *cur, t_list **lst)
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
