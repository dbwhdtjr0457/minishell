/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:58:47 by joyoo             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/13 13:14:08 by joyoo            ###   ########.fr       */
=======
/*   Updated: 2023/03/13 13:19:53 by jihylim          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
