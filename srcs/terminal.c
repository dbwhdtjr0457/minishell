/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:25:57 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/11 20:24:49 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	term_on(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag = term.c_lflag | ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	term_off(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag = term.c_lflag & ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
