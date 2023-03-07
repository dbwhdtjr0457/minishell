/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:21:42 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/07 19:59:52 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *cmd, t_list *env)
{
	char	*path;
	char	*tmp;
	char	*tmp2;
	char	**split;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_env("PATH", env);
	if (!path)
		return (0);
	split = ft_split(path, ':');
	i = 0;
	while (split[i])
	{
		tmp2 = ft_strjoin(split[i], "/");
		tmp = ft_strjoin(tmp2, cmd);
		free(tmp2);
		if (access(tmp, X_OK) == 0)
			break ;
		free(tmp);
		tmp = 0;
		i++;
	}
	free(path);
	free_split(split);
	return (tmp);
}

int	builtin(t_mini *mini, t_list **env)
{
	if (!mini->parsed)
		return (0);
	else if (ft_strncmp((mini->parsed)[0], "echo", 5) == 0)
		ft_echo(mini);
	else if (ft_strncmp((mini->parsed)[0], "cd", 3) == 0)
		ft_cd(mini, env);
	else if (ft_strncmp((mini->parsed)[0], "pwd", 4) == 0)
		ft_pwd(mini);
	else if (ft_strncmp((mini->parsed)[0], "export", 7) == 0)
		ft_export(mini, env);
	else if (ft_strncmp((mini->parsed)[0], "unset", 6) == 0)
		ft_unset(mini, env);
	else if (ft_strncmp((mini->parsed)[0], "env", 4) == 0)
		ft_env(mini, *env);
	else if (ft_strncmp((mini->parsed)[0], "exit", 5) == 0)
		ft_exit(mini, *env);
	else
		return (0);
	return (1);
}

void	get_parsed(t_list *parsed, int type)
{
	while (parsed)
	{
		if (((t_split *)parsed->content)->type == type)
			break ;
		parsed = parsed->next;
	}
}

int	execute(t_list *mini_list, t_list **env)
{
	char	*path;
	pid_t	pid;
	char	**env_char;
	t_mini	*mini;

	mini = (t_mini *)mini_list->content;
	if (!builtin(mini, env))
	{
		env_char = env_to_char(*env);
		pid = fork();
		if (pid == 0)
		{
			check_redir(mini->redir);
			if (mini->parsed)
			{
				path = find_path((mini->parsed)[0], *env);
				if (path)
					execve(path, mini->parsed, env_char);
				else
				{
					ft_putstr_fd((mini->parsed)[0], 2);
					ft_putstr_fd(": command not found\n", 2);
					free(path);
					free_split(env_char);
					exit(127);
				}
			}
			exit(1);
		}
		else
		{
			waitpid(pid, &g_status, 0);
			g_status = (g_status & 0xff00) >> 8;
			free_split(env_char);
		}
	}
	return (1);
}

