/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:59:34 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/14 17:32:49 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

void	save_tmp(char **tmp, char *str, t_list **env)
{
	char	*tmp2;

	tmp2 = 0;
	tmp2 = get_env(str, *env);
	ft_free(tmp[1]);
	tmp[1] = tmp2;
}

int	operate_cd(char **tmp, t_list **env)
{
	char	*tmp2;

	if (!tmp[1])
	{
		tmp2 = get_env("HOME", *env);
		chdir(tmp2);
		ft_free(tmp2);
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
	return (1);
}

void	cd_parent(t_mini *mini, t_list **env)
{
	char	**tmp;
	char	*pwd;
	char	*oldpwd;

	tmp = mini->parsed;
	if (!operate_cd(tmp, env))
		return ;
	pwd = getcwd(0, 0);
	oldpwd = get_env("PWD", *env);
	set_env("OLDPWD", oldpwd, env);
	set_env("PWD", pwd, env);
	ft_free(pwd);
	ft_free(oldpwd);
	g_status = 0;
}

int	ft_cd(t_mini *mini, t_list **env)
{
	pid_t	pid;

	fork_check(&pid);
	if (pid == 0)
	{
		check_redir(mini->redir);
		exit(0);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		g_status = ((g_status & 0xff00) >> 8);
		if (g_status == 0)
			cd_parent(mini, env);
		return (1);
	}
	return (0);
}
