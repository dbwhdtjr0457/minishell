/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:13:21 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/11 20:13:48 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(void	*content)
{
	t_token	*tmp;

	if (!content)
		return ;
	tmp = (t_token *)content;
	free(tmp->token);
	free(tmp);
}

void	ft_lstclear_token(t_list **lst)
{
	t_list	*tmp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free_token((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = 0;
}

void	free_mini(t_mini *lst)
{
	t_mini	*mini;

	mini = (t_mini *)lst;
	if (mini->parsed)
		free_split(mini->parsed);
	if (mini->redir)
		ft_lstclear_token(&(mini->redir));
	if (mini)
		free(mini);
}

void	ft_lstclear_mini(t_list **lst)
{
	t_list	*tmp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free_mini((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = 0;
}
