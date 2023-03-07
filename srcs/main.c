/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:46 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/07 20:41:25 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_prompt(int signal)
{
	(void)signal;
	g_status = 128 + signal;
	// write(1, PROMPT, ft_strlen(PROMPT));
	write(1, "\n", 1);
	// 현재까지 입력된 문자열을 str로 바꿔주는 함력
	// 프롬포트를 입력하지 않고 새로운 프롬포트 출력할 때, 프롬포트 비워주기
	rl_replace_line("", 0);
	// rl_display 실행 위해 필요
	rl_on_new_line();
	// readline에 입력된 문자열 다시 출력
	rl_redisplay();
}

void	signal_c(int signal)
{
	(void)signal;
	g_status = 128 + signal;
	write(1, "^C", 2);
	write(1, "\n", 1);
}

void	signal_enter(int signal)
{
	(void)signal;
	g_status = -(128 + signal);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signal_slash(int signal)
{
	(void)signal;
	g_status = 128 + signal;
	ft_putstr_fd("^\\Quit: 3\n", 1);
}

void	signal_setting(int flag)
{
	if (flag == 1)
	{
		signal(SIGINT, signal_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == 2)
	{
		signal(SIGINT, signal_c);
		signal(SIGQUIT, signal_slash);
		// signal(SIGTERM, signal_exe);
	}
}

void	del_tmp(t_list *mini_list)
{
	t_list	*tmp;
	t_mini	*tmp_mini;
	t_list	*tmp_redir;

	tmp = mini_list;
	while (tmp)
	{
		tmp_mini = tmp->content;
		tmp_redir = tmp_mini->redir;
		while (tmp_redir)
		{
			if (access(((t_token *)tmp_redir->content)->token, F_OK) == 0)
				unlink(((t_token *)tmp_redir->content)->token);
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	char			*line;
	struct termios	term;
	t_list			*mini_list;
	t_list			*env;
	t_list			*tmp;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	make_env(&env, envp);
	while (1)
	{
		signal_setting(1);
		line = readline(PROMPT);
		if (!line)
		{
			// ctrl + D 눌렀을 경우
			// 한줄 올리고 커서 12 만큼 앞으로 해서 exit 출력하고 while 빠져나가기
			ft_putstr_fd("\033[1A\033[12Cexit\n", 1);
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
					{
						del_tmp(mini_list);
						break ;
					}
					tmp = tmp->next;
				}
				if (!tmp)
				{
					signal_setting(2);
					if (ft_lstsize(mini_list) > 1)
						pipe_execute(mini_list, &env);
					else
						execute(mini_list, &env);
				}
				ft_lstclear_mini(&mini_list);
			}
		}
		// printf("g_status: %d\n", g_status);
	}
	(void)ac;
	(void)av;
	ft_lstclear_env(&env);
	// system("leaks minishell");
	return (0);
}
