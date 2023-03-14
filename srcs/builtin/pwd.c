/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:57:44 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/14 19:11:40 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_pwd(t_mini *mini)
{
	char	*pwd;
	pid_t	pid;

	ft_fork(&pid);
	if (pid == 0)
	{
		check_redir(mini->redir);
		pwd = getcwd(0, 0);
		ft_putstr_fd(pwd, 1);
		ft_putchar_fd('\n', 1);
		ft_free(pwd);
		exit(0);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		g_status = (g_status & 0xff00) >> 8;
	}
	return (1);
}
