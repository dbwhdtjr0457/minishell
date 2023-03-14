/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:58:15 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/14 18:49:39 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	print_export_error(char *s1, char *s2)
{
	ft_putstr_fd("MochaShell: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	ft_export_utils(char **tmp, char **res, t_list **env)
{
	int		i;
	char	**tmp2;
	int		status;

	i = 0;
	status = 0;
	while (tmp[++i])
	{
		if (ft_strchr(tmp[i], '=') && tmp[i][0] != '=')
		{
			tmp2 = ft_split(tmp[i], '=');
			res[0] = tmp2[0];
			res[1] = ft_substr(ft_strchr(tmp[i], '=') + 1, 0,
					ft_strlen(ft_strchr(tmp[i], '=') + 1));
			set_env(res[0], res[1], env);
			free_split(tmp2);
			ft_free(res[1]);
		}
		else if (ft_strncmp(tmp[i], "=", 1))
			set_env(tmp[i], "", env);
		else
			status = print_export_error(tmp[0], tmp[i]);
	}
	return (status);
}

int	ft_export(t_mini *mini, t_list **env)
{
	char	**tmp;
	char	*res[2];
	pid_t	pid;

	tmp = mini->parsed;
	pid = fork();
	if (pid == 0)
	{
		check_redir(mini->redir);
		if (!tmp[1])
			ft_env(mini, *env, ft_lstprint_export);
		exit(0);
	}
	else
	{
		waitpid(pid, 0, 0);
		g_status = ft_export_utils(tmp, res, env);
		return (1);
	}
}
