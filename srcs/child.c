/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:28:12 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/01 03:15:31 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_pipex *pipex, t_mini *curr_mini, int list_size, int i)
{
	char	*path;

	if (i != 0)
	{
		dup2(pipex->old_pipe[0], 0);
		close(pipex->old_pipe[0]);
		close(pipex->old_pipe[1]);
	}
	if (i != list_size - 1)
	{
		dup2(pipex->new_pipe[1], 1);
		close(pipex->new_pipe[0]);
		close(pipex->new_pipe[1]);
	}
	path = find_path((curr_mini->parsed)[0], *(pipex->env));
	check_redir(curr_mini->redir);
	if (execve(path, curr_mini->parsed, pipex->envp) == -1)
	{
		perror("execve error");
		exit(1);
	}
}
