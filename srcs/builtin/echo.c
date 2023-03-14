/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:57:20 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/14 17:32:44 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	skip_option(char **tmp)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 0;
	while (tmp[++i])
	{
		if (tmp[i][0] == '-')
		{
			j = 0;
			while (tmp[i][++j])
			{
				if (tmp[i][j] != 'n')
					return (flag);
			}
			flag = i;
		}
		else
			break ;
	}
	return (flag);
}

void	ft_echo_child(t_mini *mini)
{
	int		i;
	char	**tmp;
	int		flag;

	check_redir(mini->redir);
	flag = 0;
	tmp = mini->parsed;
	flag = skip_option(tmp);
	i = flag;
	while (tmp[++i])
	{
		ft_putstr_fd(tmp[i], 1);
		if (tmp[i + 1])
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	exit(0);
}

int	ft_echo(t_mini *mini)
{
	pid_t	pid;

	fork_check(&pid);
	if (pid == 0)
		ft_echo_child(mini);
	else
	{
		waitpid(pid, &g_status, 0);
		g_status = (g_status & 0xff00) >> 8;
	}
	return (1);
}
