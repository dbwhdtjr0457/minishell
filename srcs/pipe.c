/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:11:01 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/27 16:38:09 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	perror_exit(char *str, int status)
{
	perror(str);
	exit(status);
}

void	pipex_init(t_pipex *pipex, int pipe_num, t_list **env)
{
	char	*path_str;

	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * (pipe_num + 1));
	path_str = get_env("PATH", *env);
	pipex->path_list = ft_split(path_str, ':');
	free(path_str);
	pipex->envp = env_to_char(*env);
}

void	pipex_pipe(t_pipex *pipex, int i)
{
	if (i != 0)
		pipex->old_pipe[0] = pipex->new_pipe[0];
	if (pipe(pipex->new_pipe) == -1)
		perror_exit("pipe error", 1);
}

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
	if (dup2(fd, STDOUT_FILENO) == -1)
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
	t_split	*tmp_split;

	curr = redir;
	while (curr)
	{
		tmp_split = curr->content;
		if (ft_strncmp((tmp_split->split)[0], "<",
			ft_strlen(tmp_split->split[0]) + 1) == 0)
			redir_in((tmp_split->split)[1]);
		else if (ft_strncmp((tmp_split->split)[0], ">",
			ft_strlen(tmp_split->split[0]) + 1) == 0)
			redir_out((tmp_split->split)[1]);
		else if (ft_strncmp((tmp_split->split)[0], "<<",
			ft_strlen(tmp_split->split[0]) + 1) == 0)
			redir_heredoc((tmp_split->split)[1]);
		else if (ft_strncmp((tmp_split->split)[0], ">>",
			ft_strlen(tmp_split->split[0]) + 1) == 0)
			redir_append((tmp_split->split)[1]);
		curr = curr->next;
	}
}

int	pipe_execute(t_mini *mini, t_list **env, int pipe_num)
{
	// int		i;
	t_pipex	pipex;
	// int		status;

	// i = 0;
	// status = 0;
	check_redir(mini->redir);
	pipex_init(&pipex, pipe_num, env);
	// while (i <= pipe_num)
	// {
	// 	pipex_pipe(&pipex, i);
	// 	pipex.pid[i] = fork();
	// 	if (pipex.pid[i] == 0)
	// 		pipex_child(&pipex, i, pipe_num, parsed);
	// 	else
	// 		pipex_parent(&pipex, i, pipe_num, &status);
	// 	i++;
	// }
	return (1);
}
