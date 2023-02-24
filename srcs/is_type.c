/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:10:49 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/24 14:54:06 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(t_list *lst)
{
	if (((t_token *)(lst->content))->type >= REDIR_LL
		&& ((t_token *)(lst->content))->type <= REDIR_R)
		return (1);
	return (0);
}

int	is_pipe(t_list *lst)
{
	if (((t_token *)(lst->content))->type == PIPE_T)
		return (1);
	return (0);
}

int	is_word(t_list *lst)
{
	if (((t_token *)(lst->content))->type == WORD_T)
		return (1);
	return (0);
}

int	is_space(t_list *lst)
{
	if (((t_token *)(lst->content))->type == SPACE_T)
		return (1);
	return (0);
}

int	is_double(t_list *lst)
{
	if (((t_token *)(lst->content))->type == QUOTE_DOUBLE)
		return (1);
	return (0);
}
