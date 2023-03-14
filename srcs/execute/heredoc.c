/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:08:52 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/14 22:12:52 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <stdio.h>
#include <readline/readline.h>

static void	make_tmpfile(char **tmpfile)
{
	int		num;
	char	*numstr;

	num = 0;
	numstr = ft_itoa(num);
	*tmpfile = ft_strjoin(".tmp", numstr);
	ft_free(numstr);
	while (access(*tmpfile, F_OK) == 0)
	{
		num++;
		ft_free(*tmpfile);
		numstr = ft_itoa(num);
		*tmpfile = ft_strjoin(".tmp", numstr);
		ft_free(numstr);
	}
}

static int	read_heredoc(char **line, t_token *token, char *tmpfile, int fd)
{
	*line = readline("> ");
	if (!*line)
		return (0);
	if (ft_strncmp(*line, token->token, ft_strlen(*line) + 1) == 0)
		return (0);
	if (g_status < 0)
	{
		ft_free(*line);
		close(fd);
		unlink(tmpfile);
		ft_free(tmpfile);
		g_status = -g_status;
		return (2);
	}
	ft_putstr_fd(*line, fd);
	ft_putstr_fd("\n", fd);
	ft_free(*line);
	return (1);
}

static int	change_heredoc(t_token *token)
{
	char	*line;
	char	*tmpfile;
	int		fd;
	int		tmp;

	make_tmpfile(&tmpfile);
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_open(fd);
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
	ft_free(line);
	close(fd);
	ft_free(token->token);
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
