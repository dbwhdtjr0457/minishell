/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:00:12 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/13 13:19:49 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(t_mini *mini, t_list *env, void (*print)(void*))
{
	char	**tmp;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		check_redir(mini->redir);
		tmp = mini->parsed;
		if (tmp[1])
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(tmp[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(127);
		}
		ft_lstiter(env, print);
		exit(0);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		g_status = ((g_status & 0xff00) >> 8);
	}
	return (1);
}
