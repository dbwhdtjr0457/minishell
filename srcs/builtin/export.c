/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:58:15 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/11 15:02:18 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_export(t_mini *mini, t_list **env)
{
	char	**tmp;
	char	**tmp2;
	char	*res[2];
	pid_t	pid;

	tmp = mini->parsed;
	pid = fork();
	if (pid == 0)
	{
		check_redir(mini->redir);
		if (!tmp[1])
			ft_env(mini, *env);
		exit(0);
	}
	else
	{
		waitpid(pid, 0, 0);
		if (tmp[1])
		{
			if (ft_strchr(tmp[1], '='))
			{
				tmp2 = ft_split(tmp[1], '=');
				res[0] = tmp2[0];
				res[1] = ft_substr(ft_strchr(tmp[1], '=') + 1, 0,
						ft_strlen(ft_strchr(tmp[1], '=') + 1));
				set_env(res[0], res[1], env);
				free_split(tmp2);
				free(res[1]);
			}
			else
				set_env(tmp[1], "", env);
		}
		g_status = 0;
		return (1);
	}
}