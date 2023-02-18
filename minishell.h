/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:20:14 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/18 15:18:42 by joyoo            ###   ########.fr       */
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

enum e_token{
	QUOTE_DOUBLE = 0,
	QUOTE_SINGLE,
	REDIR_LL,
	REDIR_L,
	REDIR_RR,
	REDIR_R,
	PIPE_TOKEN,
	SPACE_TOKEN,
	DOLLAR_TOKEN,
	WORD_TOKEN
};

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

//builtin.c
int		ft_echo(t_list *parsed);
int		ft_cd(t_list *parsed, t_list **env);

//minishell.c
int		minishell(t_list *parsed, t_list **env);

// get_set_env.c
char	*get_env(t_list *env, char *key);
int		set_env(t_list **env, char *key, char *value);

// execute.c
int		split_size(char **split);
int		execute(t_list *parsed, t_list **env);

// builtin_1.c
int		ft_echo(t_list *parsed);
int		ft_pwd(t_list *parsed);
int		ft_env(t_list *parsed, t_list *env);

#endif
