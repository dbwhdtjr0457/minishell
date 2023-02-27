/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:01:16 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/28 00:18:36 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	if (!lst || !(*lst))
	//if (!(*lst))
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

void	free_parsed(void *content)
{
	t_split	*tmp;

	if (!content)
		return ;
	tmp = (t_split *)content;
	free_split(tmp->split);
	free(tmp);
}

void	ft_lstclear_parsed(t_list **lst)
{
	t_list	*tmp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free_parsed((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = 0;
}

void	ft_lstclear_env(t_list **lst)
{
	t_list	*tmp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free_split((*lst)->content);
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

	while (*lst)
	{
		tmp = (*lst)->next;
		free_mini((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}
