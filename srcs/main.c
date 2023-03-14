/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:46 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/14 19:28:24 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_list **env, char **envp)
{
	print_ascii();
	make_env(env, envp);
	set_signal(signal_prompt, SIG_IGN);
	term_off();
}

void	main_loop(char *line, t_list **env)
{
	t_list	*tmp;
	t_list	*mini_list;

	add_history(line);
	mini_list = parsing(line, *env);
	ft_free(line);
	if (!mini_list)
		return ;
	tmp = mini_list;
	while (tmp)
	{
		if (!check_heredoc(((t_mini *)tmp->content)->redir))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		term_on();
		if (ft_lstsize(mini_list) > 1)
			pipe_execute(mini_list, env);
		else
			execute(mini_list, env);
		term_off();
	}
	ft_lstclear_mini(&mini_list);
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
			ft_putstr_fd("\0338exit\n", 1);
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
