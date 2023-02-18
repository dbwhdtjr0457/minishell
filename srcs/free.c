/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:01:16 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/18 17:52:06 by joyoo            ###   ########.fr       */
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

void	free_parsed(void *content)
{
	t_split	*tmp;

	tmp = (t_split *)content;
	free_split(tmp->split);
	free(tmp);
}

void	ft_lstclear_parsed(t_list **lst)
{
	t_list	*tmp;

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

	while (*lst)
	{
		tmp = (*lst)->next;
		free_split((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = 0;
}
