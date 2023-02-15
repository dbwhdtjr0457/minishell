/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:46 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/15 15:42:18 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 이거 없으면 readline 불러올 때 error: unknown type name 'FILE' 발생
#include <stdio.h>
#include <readline/readline.h>

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		line = readline("MochaShell> ");
		if (!line)
		{
			free(line);
			line = 0;
			break ;
		}
		if (!ft_strncmp("exit", line, 4))
			break ;
	}
	return (0);
}
