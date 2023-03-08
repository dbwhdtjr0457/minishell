/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:11:01 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/07 16:46:54 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	perror_exit(char *str, int status)
{
	perror(str);
	exit(status);
}

void	pipex_init(t_pipex *pipex, int list_size, t_list **env)
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

void	pipex_pipe(t_pipex *pipex)
{
	if (pipe(pipex->new_pipe) == -1)
		perror_exit("pipe error", 1);
}

void	free_pipex(t_pipex *pipex)
{
	free_split(pipex->envp);
	free(pipex->pid);
}

int	pipe_execute(t_list *mini_list, t_list **env)
{
	t_pipex	pipex;
	t_list	*curr;
	t_mini	*curr_mini;
	int		i;

	pipex_init(&pipex, ft_lstsize(mini_list), env);
	curr = mini_list;
	i = 0;
	while (curr)
	{
		curr_mini = (t_mini *)curr->content;
		pipex_pipe(&pipex);
		pipex.pid[i] = fork();
		if (pipex.pid[i] == -1)
			perror_exit("fork error", 1);
		else if (pipex.pid[i] == 0)
			child_process(&pipex, curr_mini, ft_lstsize(mini_list), i);
		else
			parent_process(&pipex, ft_lstsize(mini_list), i);
		i++;
		curr = curr->next;
	}
	i = pipex.status;
	free_pipex(&pipex);
	return (1);
}
