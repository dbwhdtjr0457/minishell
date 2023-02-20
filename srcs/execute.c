/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:21:42 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/20 14:56:05 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	execute(t_list *parsed, t_list **env)
{
	char	**tmp;
	char	*path;
	int		i;

	tmp = ((t_split *)parsed->content)->split;
	if (ft_strncmp(tmp[0], "echo", 5) == 0)
		ft_echo(parsed);
	else if (ft_strncmp(tmp[0], "cd", 3) == 0)
		ft_cd(parsed, env);
	else if (ft_strncmp(tmp[0], "pwd", 4) == 0)
		ft_pwd(parsed);
	else if (ft_strncmp(tmp[0], "export", 7) == 0)
		ft_export(parsed, env);
	else if (ft_strncmp(tmp[0], "unset", 6) == 0)
		ft_unset(parsed, env);
	else if (ft_strncmp(tmp[0], "env", 4) == 0)
		ft_env(parsed, *env);
	else if (ft_strncmp(tmp[0], "exit", 5) == 0)
		ft_exit(parsed, *env);
	// else
	// {
	// 	path = find_path(tmp[0], *env);
	// 	if (path)
	// 	{
	// 		i = fork();
	// 		if (i == 0)
	// 			execve(path, tmp, env_to_char(*env));
	// 		else
	// 			waitpid(i, 0, 0);
	// 		free(path);
	// 	}
	// 	else
	// 		ft_putstr_fd("command not found\n", 2);
	// }
	(void)env;
	(void)i;
	(void)path;
	return (1);
}
