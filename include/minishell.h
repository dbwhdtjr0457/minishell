/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:20:14 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/13 14:11:58 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include <unistd.h>
// # include <fcntl.h>
# include <stdio.h>
// # include <stdlib.h>
// # include <string.h>
// # include <sys/wait.h>
// # include <sys/stat.h>
// # include <dirent.h>
// # include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
// # include <term.h>

# include "libft.h"
# include "get_next_line.h"
# include "execute.h"
# include "parse.h"

# define PROMPT "\033[1;33mMochaShell$ \033[0;0m\0337"

int	g_status;

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
