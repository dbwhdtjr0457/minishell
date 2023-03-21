/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:58:47 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/20 23:23:47 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

static int	check_int(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (ft_strlen(str) == i)
		return (1);
	return (0);
}

static void	exit_error(t_mini *mini)
{
	char	**tmp;

	tmp = mini->parsed;
	if (tmp[1] && check_int(tmp[1]))
	{
		g_status = ft_atoi(tmp[1]);
	}
	if (tmp[1] && !check_int(tmp[1]))
	{
		print_error_str(tmp[0], tmp[1], ": numeric argument required\n");
		g_status = 255;
		return ;
	}
	if (split_size(tmp) > 2)
	{
		print_error_str(tmp[0], tmp[1], ": too many arguments\n");
		g_status = 1;
		return ;
	}
}

int	ft_exit(t_mini *mini, t_list *env, int flag)
{
	pid_t	pid;

	ft_fork(&pid);
	if (pid == 0)
	{
		g_status = 0;
		if (flag)
			write(1, "exit\n", 5);
		check_redir(mini->redir);
		exit_error(mini);
		exit(g_status);
	}
	else
	{
		if (waitpid(pid, &g_status, 0))
		{
			(void)env;
			g_status = (g_status & 0xff00) >> 8;
			exit(g_status);
		}
	}
	return (0);
}
