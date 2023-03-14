/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:58:47 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/14 17:32:54 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

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
	if (mini->parsed[1] && check_int(mini->parsed[1]))
	{
		g_status = ft_atoi(mini->parsed[1]);
	}
	if (mini->parsed[1] && !check_int(mini->parsed[1]))
	{
		ft_putstr_fd((mini->parsed)[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_status = 255;
		return ;
	}
	if (split_size(mini->parsed) > 2)
	{
		ft_putstr_fd((mini->parsed)[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		g_status = 1;
		return ;
	}
}

int	ft_exit(t_mini *mini, t_list *env)
{
	pid_t	pid;

	fork_check(&pid);
	if (pid == 0)
	{
		g_status = 0;
		check_redir(mini->redir);
		write(1, "exit\n", 5);
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
