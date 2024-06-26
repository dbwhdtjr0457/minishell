/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:21:42 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/21 14:28:02 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtin.h"

static int	path_check(char **split, char *cmd, char **tmp, int i)
{
	char	*tmp2;

	tmp2 = ft_strjoin(split[i], "/");
	*tmp = ft_strjoin(tmp2, cmd);
	ft_free(tmp2);
	if (access(*tmp, X_OK) == 0)
		return (1);
	ft_free(*tmp);
	*tmp = 0;
	return (0);
}

char	*find_path(char *cmd, t_list *env)
{
	char	*path;
	char	*tmp;
	char	**split;
	int		i;

	if (!ft_strncmp(cmd, "\0", ft_strlen(cmd)))
		return (0);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_env("PATH", env);
	if (!path)
		return (0);
	split = ft_split(path, ':');
	ft_free(path);
	i = 0;
	while (split[i] && !path_check(split, cmd, &tmp, i))
		i++;
	free_split(split);
	return (tmp);
}

int	builtin(t_mini *mini, t_list **env, int flag)
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
		ft_env(mini, *env, ft_lstprint_env);
	else if (ft_strncmp((mini->parsed)[0], "exit", 5) == 0)
		ft_exit(mini, *env, flag);
	else
		return (0);
	return (1);
}

static void	execute_child(t_mini *mini, char **env_char, t_list **env)
{
	char	*path;

	set_signal(SIG_DFL, SIG_DFL);
	check_redir(mini->redir);
	if (mini->parsed)
	{
		path = find_path((mini->parsed)[0], *env);
		if (path)
			execve(path, mini->parsed, env_char);
		else
		{
			print_error_str((mini->parsed)[0], 0, "command not found\n");
			ft_free(path);
			free_split(env_char);
			exit(127);
		}
	}
}

int	execute(t_list *mini_list, t_list **env)
{
	pid_t	pid;
	char	**env_char;
	t_mini	*mini;

	mini = (t_mini *)mini_list->content;
	set_signal(SIG_IGN, SIG_IGN);
	if (!builtin(mini, env, 1))
	{
		env_char = env_to_char(*env);
		ft_fork(&pid);
		if (pid == 0)
		{
			execute_child(mini, env_char, env);
			exit(1);
		}
		else
		{
			waitpid(pid, &g_status, 0);
			save_g_status();
			free_split(env_char);
		}
	}
	set_signal(signal_prompt, SIG_IGN);
	return (1);
}
