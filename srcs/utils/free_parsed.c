/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:13:21 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/13 13:38:24 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!(*split))
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

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
