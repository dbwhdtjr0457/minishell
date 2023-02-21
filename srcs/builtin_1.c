/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:42:37 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/22 01:18:47 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_list *parsed)
{
	int		i;
	int		flag;
	char	**tmp;

	flag = 0;
	tmp = ((t_split *)parsed->content)->split;
	if (tmp[1] && ft_strncmp(tmp[1], "-n", 2) == 0)
		flag = 1;
	i = flag;
	while (tmp[++i])
	{
		ft_putstr_fd(tmp[i], 1);
		if (tmp[i + 1])
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (1);
}

int	ft_pwd(t_list *parsed)
{
	char	*pwd;

	if (((t_split *)parsed->content)->split[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (0);
	}
	pwd = getcwd(0, 0);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	return (1);
}

int	ft_env(t_list *parsed, t_list *env)
{
	char	**tmp;

	tmp = ((t_split *)parsed->content)->split;
	if (tmp[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(tmp[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	ft_lstiter(env, ft_lstprint_env);
	return (1);
}

int	ft_exit(t_list *parsed, t_list *env)
{
	ft_lstclear_env(&env);
	ft_lstclear_parsed(&parsed);
	exit(0);
}

void	save_tmp(char **tmp, char *str, t_list **env)
{
	char	*tmp2;

	tmp2 = 0;
	tmp2 = get_env(str, *env);
	free(tmp[1]);
	tmp[1] = tmp2;
}

int	ft_cd(t_list *parsed, t_list **env)
{
	char	**tmp;
	char	*pwd;
	char	*oldpwd;
	char	*tmp2;

	tmp = ((t_split *)parsed->content)->split;
	if (!tmp[1])
	{
		tmp2 = get_env("HOME", *env);
		chdir(tmp2);
		free(tmp2);
	}
	else
	{
		if (!ft_strncmp(tmp[1], "~", 1) || !ft_strncmp(tmp[1], "~/", 2))
			save_tmp(tmp, "HOME", env);
		else if (!ft_strncmp(tmp[1], "-", 1))
			save_tmp(tmp, "OLDPWD", env);
		if (chdir(tmp[1]) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(tmp[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (0);
		}
	}
	pwd = getcwd(0, 0);
	oldpwd = get_env("PWD", *env);
	set_env("OLDPWD", oldpwd, env);
	set_env("PWD", pwd, env);
	free(pwd);
	free(oldpwd);
	return (1);
}

int	ft_export(t_list *parsed, t_list **env)
{
	char	**tmp;
	char	**tmp2;

	tmp = ((t_split *)parsed->content)->split;
	if (!tmp[1])
		ft_env(parsed, *env);
	else if (ft_strchr(tmp[1], '='))
	{
		tmp2 = ft_split(tmp[1], '=');
		set_env(tmp2[0], tmp2[1], env);
		free_split(tmp2);
	}
	else
		set_env(tmp[1], "", env);
	return (1);
}

void	ft_lstremove_if(t_list **lst, void *data_ref, int (*cmp)())
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *lst;
	prev = 0;
	while (tmp)
	{
		if (!cmp(((char **)tmp->content)[0], data_ref, ft_strlen(data_ref)))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*lst = tmp->next;
			free_split(tmp->content);
			free(tmp);
			tmp = prev->next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

int	ft_unset(t_list *parsed, t_list **env)
{
	char	**tmp;
	int		i;

	tmp = ((t_split *)parsed->content)->split;
	i = 0;
	while (tmp[++i])
		ft_lstremove_if(env, tmp[i], ft_strncmp);
	return (1);
}
