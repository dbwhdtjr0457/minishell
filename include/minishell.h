/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:20:14 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/14 19:04:11 by joyoo            ###   ########.fr       */
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

# include "libft.h"
# include "execute.h"
# include "parse.h"
# include "setting.h"

# define PROMPT "\033[1;33mMochaShell$ \033[0;0m\0337"

int	g_status;

#endif
