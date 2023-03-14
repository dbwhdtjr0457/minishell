/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:11:01 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/13 16:41:20 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <stdio.h>

void	perror_exit(char *str, int status)
{
	perror(str);
	exit(status);
}

static void	pipex_init(t_pipex *pipex, int list_size, t_list **env)
{
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * list_size);
	pipex->envp = env_to_char(*env);
	pipex->old_pipe[0] = 0;
	pipex->old_pipe[1] = 0;
	pipex->new_pipe[0] = 0;
	pipex->new_pipe[1] = 0;
	pipex->status = 0;
	pipex->env = env;
}

static void	free_pipex(t_pipex *pipex)
{
	free_split(pipex->envp);
	ft_free(pipex->pid);
}

static void	pipe_cycle(t_pipex *pipex, t_list *curr, int list_size, int i)
{
	t_mini	*curr_mini;

	curr_mini = (t_mini *)curr->content;
	set_signal(SIG_IGN, SIG_IGN);
	if (pipe(pipex->new_pipe) == -1)
		perror_exit("pipe error", 1);
	pipex->pid[i] = fork();
	if (pipex->pid[i] == -1)
		perror_exit("fork error", 1);
	else if (pipex->pid[i] == 0)
		child_process(pipex, curr_mini, list_size, i);
	else
		parent_process(pipex, list_size, i);
}

int	pipe_execute(t_list *mini_list, t_list **env)
{
	t_pipex	pipex;
	t_list	*curr;
	int		i;

	pipex_init(&pipex, ft_lstsize(mini_list), env);
	curr = mini_list;
	i = 0;
	while (curr)
	{
		pipe_cycle(&pipex, curr, ft_lstsize(mini_list), i);
		i++;
		curr = curr->next;
	}
	i = pipex.status;
	free_pipex(&pipex);
	set_signal(signal_prompt, SIG_IGN);
	return (1);
}
