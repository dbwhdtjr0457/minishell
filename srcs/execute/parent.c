/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:53:39 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/12 23:54:58 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(t_pipex *pipex, int list_size, int i)
{
	int	j;

	if (i != 0)
	{
		close(pipex->old_pipe[0]);
		close(pipex->old_pipe[1]);
	}
	if (i != list_size - 1)
	{
		pipex->old_pipe[0] = pipex->new_pipe[0];
		pipex->old_pipe[1] = pipex->new_pipe[1];
	}
	if (i == list_size - 1)
	{
		j = 0;
		while (j < list_size)
		{
			waitpid(pipex->pid[j], &g_status, 0);
			j++;
		}
		save_g_status();
	}
}
