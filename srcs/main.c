/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:46 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/11 17:52:31 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_ascii(void)
{
	int		fd;
	char	*line;

	fd = open("./title/ascii.txt", O_RDONLY);
	if (!fd)
	{
		printf("error\n");
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n");
	free(line);
	close(fd);
}

int	main(int ac, char **av, char **envp)
{
	char			*line;
	t_list			*mini_list;
	t_list			*env;
	t_list			*tmp;

	print_ascii();
	make_env(&env, envp);
	set_signal(signal_prompt, SIG_IGN);
	term_off();
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			ft_putstr_fd("\0338exit\n", 1);
			break ;
		}
		else if (*line == '\0')
			free(line);
		else
		{
			add_history(line);
			mini_list = parsing(line, env);
			free(line);
			if (mini_list)
			{
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
						pipe_execute(mini_list, &env);
					else
						execute(mini_list, &env);
					term_off();
				}
				ft_lstclear_mini(&mini_list);
			}
		}
	}
	(void)ac;
	(void)av;
	ft_lstclear_env(&env);
	return (0);
}
