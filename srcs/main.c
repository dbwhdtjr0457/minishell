/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:46 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/20 10:27:42 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(t_list **env, char **envp)
{
	print_ascii();
	make_env(env, envp);
	set_signal(signal_prompt, SIG_IGN);
	term_off();
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_list	*env;

	init(&env, envp);
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			ft_putstr_fd("\033[A\033[12Cexit\n", 1);
			break ;
		}
		else if (*line == '\0')
			ft_free(line);
		else
			main_loop(line, &env);
	}
	(void)ac;
	(void)av;
	ft_lstclear_env(&env);
	return (0);
}
