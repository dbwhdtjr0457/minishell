/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:00:12 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/14 19:01:46 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(t_mini *mini, t_list *env, void (*print)(void*))
{
	char	**tmp;
	pid_t	pid;

	fork_check(&pid);
	if (pid == 0)
	{
		check_redir(mini->redir);
		tmp = mini->parsed;
		if (tmp[1])
		{
			print_error_str(tmp[0], tmp[1], ": No such file or directory\n");
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
