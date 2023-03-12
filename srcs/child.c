/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:28:12 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/11 15:45:54 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_dup(t_pipex *pipex, int i, int list_size)
{
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
}

void	child_process(t_pipex *pipex, t_mini *curr_mini, int list_size, int i)
{
	char	*path;

	set_signal(SIG_DFL, SIG_DFL);
	set_dup(pipex, i, list_size);
	check_redir(curr_mini->redir);
	if (!builtin(curr_mini, pipex->env) && curr_mini->parsed)
	{
		path = find_path((curr_mini->parsed)[0], *(pipex->env));
		if (path)
			execve(path, curr_mini->parsed, pipex->envp);
		else
		{
			printf("%s: command not found\n", (curr_mini->parsed)[0]);
			exit(127);
		}
	}
	exit(g_status);
}
