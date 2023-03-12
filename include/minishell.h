/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:20:14 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/12 23:53:37 by jihylim          ###   ########.fr       */
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

# include "libft.h"
# include "get_next_line.h"
# include "parse.h"

# define PROMPT "\033[1;33mMochaShell$ \033[0;0m\0337"

int	g_status;

typedef struct s_pipex
{
	char	**path_list;
	char	*cmd_path;
	int		new_pipe[2];
	int		old_pipe[2];
	pid_t	*pid;
	int		argc;
	char	**argv;
	char	**envp;
	t_list	**env;
	int		status;
}	t_pipex;

// free_env.c
void	ft_lstclear_env(t_list **lst);


// print_list.c
void	print_word_in_list(void *content);
void	print_mini(void *content);
void	ft_lstprint_env(void *content);
void	ft_lstprint_export(void *content);

/////////////////////////////////////////////

// execute.c
int		split_size(char **split);
int		execute(t_list *mini_list, t_list **env);
char	*find_path(char *cmd, t_list *env);
int		builtin(t_mini *mini, t_list **env);

// builtin_1.c
int		ft_echo(t_mini *mini);
int		ft_pwd(t_mini *mini);
int		ft_env(t_mini *mini, t_list *env, void (*print)(void*));
int		ft_exit(t_mini *mini, t_list *env);
int		ft_cd(t_mini *mini, t_list **env);
int		ft_export(t_mini *mini, t_list **env);
int		ft_unset(t_mini *mini, t_list **env);

// env_utils.c
void	make_env(t_list **env, char **envp);
char	*get_env(char *key, t_list *env);
void	set_env(char *key, char *value, t_list **env);

// pipe.c
void	perror_exit(char *str, int status);
int		pipe_execute(t_list *mini_list, t_list **env);

// redir.c
void	redir_in(t_token *redir);
void	redir_out(char *file);
int		check_heredoc(t_list *redir);
void	redir_append(char *file);
void	check_redir(t_list *redir);

// utils.c
int		split_size(char **split);
char	**env_to_char(t_list *env);

// child.c
void	child_process(t_pipex *pipex, t_mini *curr_mini, int list_size, int i);

// parent.c
void	parent_process(t_pipex *pipex, int list_size, int i);

// signal.c
void	signal_prompt(int signal);
void	signal_heredoc(int signal);
void	set_signal(void (*f1)(int), void (*f2)(int));
void	save_g_status(void);

// terminal.c
void	term_on(void);
void	term_off(void);

#endif
