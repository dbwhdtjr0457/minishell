/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:08:52 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/12 23:54:58 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_tmpfile(char **tmpfile)
{
	int		num;
	char	*numstr;

	num = 0;
	numstr = ft_itoa(num);
	*tmpfile = ft_strjoin(".tmp", numstr);
	free(numstr);
	while (access(*tmpfile, F_OK) == 0)
	{
		num++;
		free(*tmpfile);
		numstr = ft_itoa(num);
		*tmpfile = ft_strjoin(".tmp", numstr);
		free(numstr);
	}
}

int	read_heredoc(char **line, t_token *token, char *tmpfile, int fd)
{
	*line = readline("> \0337");
	if (!*line)
	{
		ft_putstr_fd("\0338", 1);
		return (0);
	}
	if (ft_strncmp(*line, token->token, ft_strlen(*line) + 1) == 0)
		return (0);
	if (g_status < 0)
	{
		free(*line);
		close(fd);
		unlink(tmpfile);
		free(tmpfile);
		g_status = -g_status;
		return (2);
	}
	ft_putstr_fd(*line, fd);
	ft_putstr_fd("\n", fd);
	free(*line);
	return (1);
}

int	change_heredoc(t_token *token)
{
	char	*line;
	char	*tmpfile;
	int		fd;
	int		tmp;

	make_tmpfile(&tmpfile);
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	set_signal(signal_heredoc, SIG_IGN);
	line = 0;
	while (1)
	{
		tmp = read_heredoc(&line, token, tmpfile, fd);
		if (tmp == 0)
			break ;
		else if (tmp == 2)
			return (0);
	}
	free(line);
	close(fd);
	free(token->token);
	token->token = tmpfile;
	return (1);
}

int	check_heredoc(t_list *redir)
{
	t_list	*curr;
	t_token	*tmp_redir;

	curr = redir;
	while (curr)
	{
		tmp_redir = curr->content;
		if (tmp_redir->type == REDIR_LL && !change_heredoc(tmp_redir))
			return (0);
		curr = curr->next;
	}
	return (1);
}
