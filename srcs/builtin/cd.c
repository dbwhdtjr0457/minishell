/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:59:34 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/11 14:59:41 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	save_tmp(char **tmp, char *str, t_list **env)
{
	char	*tmp2;

	tmp2 = 0;
	tmp2 = get_env(str, *env);
	free(tmp[1]);
	tmp[1] = tmp2;
}

int	ft_cd(t_mini *mini, t_list **env)
{
	char	**tmp;
	char	*pwd;
	char	*oldpwd;
	char	*tmp2;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		check_redir(mini->redir);
		exit(0);
	}
	else
	{
		waitpid(pid, 0, 0);
		tmp = mini->parsed;
		if (!tmp[1])
		{
			tmp2 = get_env("HOME", *env);
			chdir(tmp2);
			free(tmp2);
		}
		else
		{
			if (!ft_strncmp(tmp[1], "~", 2) || !ft_strncmp(tmp[1], "~/", 3))
				save_tmp(tmp, "HOME", env);
			else if (!ft_strncmp(tmp[1], "-", 1))
				save_tmp(tmp, "OLDPWD", env);
			if (chdir(tmp[1]) == -1)
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd(tmp[1], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_status = 1;
				return (0);
			}
		}
		pwd = getcwd(0, 0);
		oldpwd = get_env("PWD", *env);
		set_env("OLDPWD", oldpwd, env);
		set_env("PWD", pwd, env);
		free(pwd);
		free(oldpwd);
		g_status = 0;
		return (1);
	}
}