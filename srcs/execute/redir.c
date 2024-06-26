/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:05:10 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/14 19:12:02 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	redir_in(t_token *token)
{
	int	fd;

	fd = open(token->token, O_RDONLY);
	ft_open(fd);
	ft_dup2(fd, 0);
	if (token->type == REDIR_LL)
		unlink(token->token);
	close(fd);
}

static void	redir_out(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_open(fd);
	ft_dup2(fd, 1);
	close(fd);
}

static void	redir_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_open(fd);
	ft_dup2(fd, 1);
	close(fd);
}

void	check_redir(t_list *redir)
{
	t_list	*curr;
	t_token	*tmp_redir;

	curr = redir;
	while (curr)
	{
		tmp_redir = curr->content;
		if (tmp_redir->type == REDIR_L || tmp_redir->type == REDIR_LL)
			redir_in(tmp_redir);
		else if (tmp_redir->type == REDIR_R)
			redir_out(tmp_redir->token);
		else if (tmp_redir->type == REDIR_RR)
			redir_append(tmp_redir->token);
		curr = curr->next;
	}
}
