/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:21:42 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/27 23:54:04 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

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

char	**env_to_char(t_list *env)
{
	char	**tmp;
	char	*tmp2;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	i = 0;
	while (env)
	{
		tmp2 = ft_strjoin(((char **)env->content)[0], "=");
		tmp[i] = ft_strjoin(tmp2, ((char **)env->content)[1]);
		free(tmp2);
		env = env->next;
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

int	builtin(t_mini *mini, t_list **env, char **tmp)
{
	// mini 형식에 맞춰서 바꿔야함!
	// if (ft_lstsize(mini->parsed) > 1)
	// 	return (0);
	if (ft_strncmp(tmp[0], "echo", 5) == 0)
		ft_echo(mini);
	else if (ft_strncmp(tmp[0], "cd", 3) == 0)
		ft_cd(mini, env);
	else if (ft_strncmp(tmp[0], "pwd", 4) == 0)
		ft_pwd(mini);
	else if (ft_strncmp(tmp[0], "export", 7) == 0)
		ft_export(mini, env);
	else if (ft_strncmp(tmp[0], "unset", 6) == 0)
		ft_unset(mini, env);
	else if (ft_strncmp(tmp[0], "env", 4) == 0)
		ft_env(mini, *env);
	else if (ft_strncmp(tmp[0], "exit", 5) == 0)
		ft_exit(mini, *env);
	else
		return (0);
	return (1);
}

int	pipe_count(t_list *parsed)
{
	int	pipe_num;

	pipe_num = 0;
	while (parsed)
	{
		if (((t_split *)parsed->content)->type == PIPE_T)
			pipe_num++;
		parsed = parsed->next;
	}
	return (pipe_num);
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

int	execute(t_mini *mini, t_list **env)
{
	char	**tmp;
	char	*path;
	pid_t	pid;
	pid_t	pid2;
	char	**env_char;

	// 일단 내가 바꿈
	tmp = mini->parsed;
	if (!builtin(mini, env, tmp))
	{
		{
			env_char = env_to_char(*env);
			pid = fork();
			if (pid == 0)
			{
				check_redir(mini->redir);
				// 일단 내가 바꿈22
				tmp = mini->parsed;
				path = find_path(tmp[0], *env);
				if (path)
				{
					pid2 = fork();
					if (pid2 == 0)
						execve(path, tmp, env_char);
					else
						waitpid(pid2, 0, 0);
				}
				else
				{
					ft_putstr_fd(tmp[0], 2);
					ft_putstr_fd(": command not found\n", 2);
				}
				free(path);
				free_split(env_char);
				exit(0);
			}
			else
			{
				waitpid(pid, 0, 0);
				free_split(env_char);
			}
		}
	}
	return (1);
}

