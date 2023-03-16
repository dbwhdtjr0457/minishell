/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:59:34 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/16 14:52:11 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	save_tmp(char **tmp, char *str, t_list **env)
{
	char	*tmp2;

	tmp2 = 0;
	tmp2 = get_env(str, *env);
	ft_free(tmp[1]);
	tmp[1] = tmp2;
}

int	special_dir(char **tmp, t_list **env)
{
	char	*tmp_oldpwd;

	if (!ft_strncmp(tmp[1], "~", 2) || !ft_strncmp(tmp[1], "~/", 3))
		save_tmp(tmp, "HOME", env);
	else if (!ft_strncmp(tmp[1], "-", 1))
	{
		tmp_oldpwd = get_env("OLDPWD", *env);
		if (!tmp_oldpwd)
		{
			ft_putstr_fd("MochaShell: cd: OLDPWD not set\n", 2);
			g_status = 1;
			return (0);
		}
		save_tmp(tmp, "OLDPWD", env);
		ft_free(tmp_oldpwd);
	}
	return (1);
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
		if (!special_dir(tmp, env))
			return (0);
		if (chdir(tmp[1]) == -1)
		{
			print_error_str(tmp[0], tmp[1], ": No such file or directory\n");
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
	oldpwd = getcwd(0, 0);
	if (!operate_cd(tmp, env))
	{
		ft_free(oldpwd);
		return ;
	}
	pwd = getcwd(0, 0);
	set_env("OLDPWD", oldpwd, env);
	set_env("PWD", pwd, env);
	ft_free(pwd);
	ft_free(oldpwd);
	g_status = 0;
}

int	ft_cd(t_mini *mini, t_list **env)
{
	pid_t	pid;

	ft_fork(&pid);
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
