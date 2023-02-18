/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:42:37 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/18 15:24:45 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_list *parsed)
{
	int		i;
	int		flag;
	char	**tmp;

	i = 0;
	flag = 0;
	tmp = ((t_token *)parsed->content)->context;
	if (tmp[1] && ft_strncmp(tmp[1], "-n", 2) == 0)
		flag = 1;
	while (tmp[++i])
	{
		ft_putstr_fd(tmp[i], 1);
		if (tmp[i + 1])
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_pwd(t_list *parsed)
{
	char	*pwd;

	if (((t_token *)parsed->content)->context[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (1);
	}
	pwd = getcwd(0, 0);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	return (0);
}

int	ft_env(t_list *parsed, t_list *env)
{
	char	**tmp;

	tmp = ((t_token *)parsed->content)->context;
	if (tmp[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(tmp[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	while (env)
	{
		ft_putstr_fd(((char **)env->content)[0], 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(((char **)env->content)[1], 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
	return (0);
}
