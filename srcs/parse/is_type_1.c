/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:10:49 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/16 20:58:03 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_double(t_list *lst)
{
	if (((t_token *)(lst->content))->type == QUOTE_DOUBLE)
		return (1);
	return (0);
}

int	is_single(t_list *lst)
{
	if (((t_token *)(lst->content))->type == QUOTE_SINGLE)
		return (1);
	return (0);
}

int	is_quote(t_list *lst)
{
	if (is_double(lst) || is_single(lst))
		return (1);
	return (0);
}

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
