/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:25:29 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/13 15:46:30 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTING_H
# define SETTING_H

# include <unistd.h>
# include <stdio.h>
# include "get_next_line.h"

extern int	g_status;

// # include <stdio.h>
// print_ascii.c
void	print_ascii(void);

// signal.c
void	signal_prompt(int signal);
void	signal_heredoc(int signal);
void	set_signal(void (*f1)(int), void (*f2)(int));
void	save_g_status(void);

// terminal.c
void	term_on(void);
void	term_off(void);

#endif
