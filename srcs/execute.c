/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:21:42 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/18 15:36:46 by joyoo            ###   ########.fr       */
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

	tmp = ((t_token *)parsed->content)->context;
	if (ft_strncmp(tmp[0], "echo", 4) == 0)
		ft_echo(parsed);
	// else if (ft_strcmp(tmp[0], "cd") == 0)
	// 	ft_cd(parsed, env);
	if (ft_strncmp(tmp[0], "pwd", 3) == 0)
		ft_pwd(parsed);
	// else if (ft_strcmp(tmp[0], "export") == 0)
	// 	ft_export(parsed, env);
	// else if (ft_strcmp(tmp[0], "unset") == 0)
	// 	ft_unset(parsed, env);
	if (ft_strncmp(tmp[0], "env", 3) == 0)
		ft_env(parsed, *env);
	// else if (ft_strcmp(tmp[0], "exit") == 0)
	// 	ft_exit(parsed);
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
