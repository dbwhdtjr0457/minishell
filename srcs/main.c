/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:46 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/09 21:26:54 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*line;
	t_list			*mini_list;
	t_list			*env;
	t_list			*tmp;

	make_env(&env, envp);
	set_signal(signal_prompt, SIG_IGN);
	term_off();
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			// ctrl + D 눌렀을 경우
			// 한줄 올리고 커서 12 만큼 앞으로 해서 exit 출력하고 while 빠져나가기
			ft_putstr_fd("\0338exit\n", 1);
			break ;
		}
		//아무것도 입력 안하고 엔터만 쳤을 때, history 에 기록 안하도록
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
		//printf("g_status: %d\n", g_status);
	}
	(void)ac;
	(void)av;
	ft_lstclear_env(&env);
	// system("leaks minishell");
	return (0);
}
