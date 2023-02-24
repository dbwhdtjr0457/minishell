/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:11:01 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/24 15:13:15 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	check_redir(t_list **parsed)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		i;

	tmp = *parsed;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, ">") == 0)
		{
			tmp2 = tmp->next;
			i = open(tmp2->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (i == -1)
				perror_exit("open error", 1);
			dup2(i, 1);
			close(i);
			tmp->content = 0;
			tmp2->content = 0;
		}
		tmp = tmp->next;
	}
	*parsed = ft_lstfilter(*parsed, 0);
	*env = ft_lstfilter(*env, 0);
}

int	pipe_execute(t_list *parsed, t_list **env, int pipe_num)
{
	int		i;
	t_pipex	pipex;
	int		status;

	i = 0;
	status = 0;
	check_redir(&parsed);
	pipex_init(&pipex, pipe_num, env);
	while (i <= pipe_num)
	{
		pipex_pipe(&pipex, i);
		pipex.pid[i] = fork();
		if (pipex.pid[i] == 0)
			pipex_child(&pipex, i, pipe_num, parsed);
		else
			pipex_parent(&pipex, i, pipe_num, &status);
		i++;
	}
	return (1);
}
