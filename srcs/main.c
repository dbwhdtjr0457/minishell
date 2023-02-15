/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:59:07 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/15 18:10:13 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 이거 없으면 readline 불러올 때 error: unknown type name 'FILE' 발생
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

void	signal_c(int signal)
{
	if (signal == SIGINT)
		write(1, "MochaShell$ \n", 15);
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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal_setting();
	while (1)
	{
		line = readline("MochaShell$ ");
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
			free(line);
		}
	}
	(void)ac;
	(void)av;
	(void)envp;
	return (0);
}
