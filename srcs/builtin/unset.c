/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:00:32 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/16 14:43:14 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_unset(t_mini *mini, t_list **env)
{
	char	**tmp;
	int		i;
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
		if (g_status != 0)
			return (1);
		tmp = mini->parsed;
		i = 0;
		while (tmp[++i])
			ft_lstremove_if(env, tmp[i], ft_strncmp);
		return (1);
	}
	return (0);
}
