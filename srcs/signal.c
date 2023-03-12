/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:26:39 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/12 23:54:58 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// rl_replace_line("", 0);
	// 현재까지 입력된 문자열을 str로 바꿔주는 함력
	// 프롬포트를 입력하지 않고 새로운 프롬포트 출력할 때, 프롬포트 비워주기
// 	rl_redisplay();
	// readline에 입력된 문자열 다시 출력

void	signal_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	signal_heredoc(int signal)
{
	(void)signal;
	g_status = -(128 + signal);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	set_signal(void (*f1)(int), void (*f2)(int))
{
	signal(SIGINT, f1);
	signal(SIGQUIT, f2);
}

void	save_g_status(void)
{
	if (g_status == 2)
	{
		g_status = 128 + g_status;
		write(1, "\n", 1);
	}
	else if (g_status == 3)
	{
		g_status = 128 + g_status;
		ft_putstr_fd("Quit: 3\n", 1);
	}
	else
		g_status = (g_status & 0xff00) >> 8;
}
