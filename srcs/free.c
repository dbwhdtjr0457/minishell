/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:01:16 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/18 17:53:40 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_token(t_list *lst, void (*del)(void *))
{
	t_token	*token;

	token = (t_token *)lst->content;
	del(token->token);
	del(lst->content);
	free(lst);
	lst = 0;
}

void	ft_lstclear_token(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free_token(*lst, del);
		*lst = tmp;
	}
	*lst = 0;
}