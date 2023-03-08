/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_comb_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:46:55 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/08 22:56:45 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	save_after_redir(t_list **lst, t_list **res, t_list *cur)
{
	char	*tmp;
	t_token	*token;

	token = (t_token *)(cur->content);
	tmp = ft_strdup(token->token);
	if (!tmp)
		return (0);
	ft_lstadd_back(res, ft_lstnew
		(new_token(tmp, ((t_token *)((*lst)->content))->type)));
	(*lst) = cur;
	return (1);
}

int	comb_redir(t_list **lst, t_list **res)
{
	t_list	*cur;
	t_token	*token;

	cur = (*lst)->next;
	while (cur)
	{
		token = (t_token *)(cur->content);
		if (token->type == SPACE_T)
			;
		else if (!is_space(cur) && !is_pipe(cur) && !is_redir(cur))
			return (save_after_redir(lst, res, cur));
		else if (token->type == PIPE_T || is_redir(cur))
		{
			print_syn_error(cur, 0);
			return (0);
		}
		cur = cur->next;
	}
	print_syn_error(0, "'newline'\n");
	return (0);
}
