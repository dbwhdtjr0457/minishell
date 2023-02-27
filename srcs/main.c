/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:46 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/27 16:35:35 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_c(int signal)
{
	if (signal == SIGINT)
	{
		write(1, PROMPT, ft_strlen(PROMPT));
		write(1, "\n", 1);
	}
	// 현재까지 입력된 문자열을 str로 바꿔주는 함력
	// 프롬포트를 입력하지 않고 새로운 프롬포트 출력할 때, 프롬포트 비워주기
	rl_replace_line("", 1);
	// rl_display 실행 위해 필요
	rl_on_new_line();
	// readline에 입력된 문자열 다시 출력
	rl_redisplay();
}

void	signal_setting(void)
{
	signal(SIGINT, signal_c);
	signal(SIGQUIT, SIG_IGN);
}

t_list	*test_parsing(void)
{
	t_list	*test;
	t_split	*split;

	test = 0;
	split = (t_split *)malloc(sizeof(t_split));
	split->type = WORD_T;
	split->split = ft_split("export a", ' ');
	ft_lstadd_back(&test, ft_lstnew(split));
	// ft_lstiter(test, ft_lstprint_input);
	return (test);
}

int	main(int ac, char **av, char **envp)
{
	char			*line;
	struct termios	term;
	t_mini			*mini;
	t_list			*env;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal_setting();
	make_env(&env, envp);
	while (1)
	{
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
			mini = parsing(line, env);
			free(line);
			if (parsed)
			{
				execute(parsed, &env);
				ft_lstclear_mini(&parsed);
			}
		}
	}
	(void)ac;
	(void)av;
	ft_lstclear_env(&env);
	// system("leaks minishell");
	return (0);
}
