/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syn_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:23:39 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/08 21:24:01 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*put_redir(t_list *lst)
{
	int	type;

	type = ((t_token *)(lst->content))->type;
	if (type == REDIR_L)
		return ("'<'\n");
	else if (type == REDIR_LL)
		return ("'<<'\n");
	else if (type == REDIR_R)
		return ("'>'\n");
	else if (type == REDIR_RR)
		return ("'>>'\n");
	else if (type == PIPE_T)
		return ("'|'\n");
	return (0);
}

void	print_syn_error(t_list *lst, char *str)
{
	ft_putstr_fd("MochaShell : syntax error near unexpected token ", 2);
	if (lst)
		ft_putstr_fd(put_redir(lst), 2);
	else if (str)
		ft_putstr_fd(str, 2);
	g_status = 258;
}
