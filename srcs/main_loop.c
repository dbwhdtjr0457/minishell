/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:41:28 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/18 14:41:29 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	main_loop_execute(t_list *mini_list, t_list **env)
{
	t_list	*tmp;

	tmp = mini_list;
	while (tmp)
	{
		if (!check_heredoc(((t_mini *)tmp->content)->redir))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		term_on();
		if (ft_lstsize(mini_list) > 1)
			pipe_execute(mini_list, env);
		else
			execute(mini_list, env);
		term_off();
	}
}

static void	unlink_tmpfile(t_list *mini_list)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_mini	*mini;

	tmp = mini_list;
	while (tmp)
	{
		mini = tmp->content;
		tmp2 = mini->redir;
		while (tmp2)
		{
			if (((t_token *)tmp2->content)->type == REDIR_LL && \
				access(((t_token *)tmp2->content)->token, F_OK) == 0)
				unlink(((t_token *)tmp2->content)->token);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	main_loop(char *line, t_list **env)
{
	t_list	*mini_list;

	add_history(line);
	mini_list = parsing(line, *env);
	ft_free(line);
	if (!mini_list)
		return ;
	main_loop_execute(mini_list, env);
	unlink_tmpfile(mini_list);
	ft_lstclear_mini(&mini_list);
}
