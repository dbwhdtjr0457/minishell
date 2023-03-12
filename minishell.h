/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:20:14 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/11 17:42:23 by joyoo            ###   ########.fr       */
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
# include "gnl/get_next_line.h"

# define PROMPT "\033[1;33mMochaShell$ \033[0;0m\0337"

int	g_status;

enum e_token
{
	QUOTE_DOUBLE = 1,
	QUOTE_SINGLE,
	REDIR_LL,
	REDIR_L,
	REDIR_RR,
	REDIR_R,
	PIPE_T,
	SPACE_T,
	DOLLAR_T,
	WORD_T
};

typedef struct s_token
{
	int		type;
	char	*token;
}	t_token;

typedef struct s_mini
{
	t_list	*redir;
	char	**parsed;
}	t_mini;

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

// free.c
void	free_split(char **split);
void	free_token(void	*content);
void	ft_lstclear_token(t_list **lst);
void	ft_lstclear_env(t_list **lst);
void	free_mini(t_mini *lst);
void	ft_lstclear_mini(t_list **mini);

// print_list.c
void	print_word_in_list(void *content);
void	print_mini(void *content);
void	ft_lstprint_env(void *content);
void	ft_lstprint_export(void *content);

//====================================================
//--------------------- parsing ----------------------
// change_to_env.c
t_list	*change_to_env(t_list *token_list, t_list *env, int flag);

// change_to_env_utils.c
char	*remove_quote(t_list *cur, t_list *env, int flag);

// is_type.c
int		is_double(t_list *lst);
int		is_single(t_list *lst);
int		is_redir(t_list *lst);
int		is_pipe(t_list *lst);
int		is_space(t_list *lst);

// is_type_2.c
int		is_dollar(t_list *lst);
int		is_word(t_list *lst);

// lexer.c
void	lexer(const char *line, int *arr);

// parse.c
t_list	*make_token(char *line, int flag);
t_list	*parsing(char *line, t_list *env);

// print_syn_error.c
char	*put_redir(t_list *lst);
void	print_syn_error(t_list *lst, char *str);

// quote_join.c
t_list	*quote_join(t_list *lst);

// split_env.c
t_list	*split_env(t_list *lst);

// token_comb.c
t_list	*quote_join(t_list *lst);
t_list	*token_comb(t_list *token_list);

// token_comb_redir.c
int		comb_redir(t_list **lst, t_list **res);

// token_list.c
t_token	*new_token(char *input, int type);
void	make_token_list(t_list **split_word, char *line, int *arr, int flag);

// token_utils.c
char	*token_join(t_list *token_list);
t_list	*token_del(t_list *pre, t_list *cur, t_list **lst);

//--------------------- parsing ----------------------
//====================================================

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
