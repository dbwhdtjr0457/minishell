/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:01:16 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/13 16:37:11 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstclear_env(t_list **lst)
{
	t_list	*tmp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free_split((*lst)->content);
		ft_free(*lst);
		*lst = tmp;
	}
	*lst = 0;
}
