/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:20:14 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/16 18:05:15 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <term.h>

# include "libft/libft.h"

# define PROMPT "minishell$ "

# define WORD_TOKEN		1
# define CMD_TOKEN 		2
# define OPT_TOKEN		3
# define ARG_TOKEN		4
# define PIPE_TOKEN		5
# define REDIR_TOKEN	6
# define SPACE_TOKEN	7
# define QUOTE_TOKEN	8
# define DOLLAR_TOKEN	9

typedef struct s_env
{
	char		*key;
	char		*value;
}	t_env;

typedef struct s_token{
	int				type;
	char			**context;
}	t_token;

// free.c
void	free_split(char **split);

// make_env.c
void	make_env(t_list **env, char **envp);

// parse.c
t_list	*parsing(char *line);

#endif
