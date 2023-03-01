/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:05:10 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/01 02:50:55 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror_exit("open error", 1);
	if (dup2(fd, 0) == -1)
		perror_exit("dup2 error", 1);
	close(fd);
}

void	redir_out(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror_exit("open error", 1);
	if (dup2(fd, 1) == -1)
		perror_exit("dup2 error", 1);
	close(fd);
}

void	redir_heredoc(char *file)
{
	char	*line;
	int		fd;

	fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, file, ft_strlen(line) + 1) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free(line);
	close(fd);
	fd = open(".tmp", O_RDONLY);
	if (fd == -1)
		perror_exit("open error", 1);
	if (dup2(fd, 0) == -1)
		perror_exit("dup2 error", 1);
	close(fd);
	unlink(".tmp");
}

void	redir_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror_exit("open error", 1);
	if (dup2(fd, 1) == -1)
		perror_exit("dup2 error", 1);
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
		if (tmp_redir->type == REDIR_L)
			redir_in(tmp_redir->token);
		else if (tmp_redir->type == REDIR_R)
			redir_out(tmp_redir->token);
		else if (tmp_redir->type == REDIR_LL)
			redir_heredoc(tmp_redir->token);
		else if (tmp_redir->type == REDIR_RR)
			redir_append(tmp_redir->token);
		curr = curr->next;
	}
}
