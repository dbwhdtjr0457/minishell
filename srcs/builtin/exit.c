/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:58:47 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/13 13:14:08 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_mini *mini, t_list *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		check_redir(mini->redir);
		exit(0);
	}
	else
	{
		if (waitpid(pid, 0, 0))
		{
			(void)env;
			exit(0);
		}
	}
	return (0);
}
