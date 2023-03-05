/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:20:14 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/05 15:11:15 by jihylim          ###   ########.fr       */
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

# define PROMPT "\033[1;33mMochaShell$ \033[0;0m"

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

typedef struct s_split
{
	int		type;
	char	**split;
}	t_split;

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
void	free_parsed(void *content);
void	ft_lstclear_parsed(t_list **lst);
void	ft_lstclear_env(t_list **lst);
void	free_mini(t_mini *lst);
void	ft_lstclear_mini(t_list **mini);

// change_to_env.c
char	*token_join(t_list *token_list);
t_list	*del_token(t_list *pre, t_list *cur, t_list **lst);
t_list	*change_to_env(t_list *token_list, t_list *env, int flag);

// lexer.c
void	lexer(const char *line, int *arr);

// parse.c
void	print_word_in_list(void *content);
t_list	*make_token(char *line);
t_list	*parsing(char *line, t_list *env);
void	print_mini(void *content);

// is_type.c
int		is_redir(t_list *lst);
int		is_pipe(t_list *lst);
int		is_word(t_list *lst);
int		is_space(t_list *lst);
int		is_dollar(t_list *lst);
int		is_double(t_list *lst);
char	*put_redir(t_list *lst);
void	print_syn_error(t_list *lst, char *str);

// token_comb.c
t_list	*split_env(t_list *lst);
t_list	*quote_join(t_list *lst);
t_list	*token_comb(t_list *token_list);

// token_list.c
t_token	*new_token(char *input, int type);
void	make_token_list(t_list **split_word, char *line, int *arr);

// make_env.c
void	make_env(t_list **env, char **envp);

// execute.c
int		split_size(char **split);
int		execute(t_list *mini_list, t_list **env);
char	*find_path(char *cmd, t_list *env);
int		builtin(t_mini *mini, t_list **env, char **tmp);

// builtin_1.c
int		ft_echo(t_mini *mini);
int		ft_pwd(t_mini *mini);
int		ft_env(t_mini *mini, t_list *env);
int		ft_exit(t_mini *mini, t_list *env);
int		ft_cd(t_mini *mini, t_list **env);
int		ft_export(t_mini *mini, t_list **env);
int		ft_unset(t_mini *mini, t_list **env);

// env_utils.c
char	*get_env(char *key, t_list *env);
void	set_env(char *key, char *value, t_list **env);

// t_list_utils.c
void	ft_lstprint_input(void *content);
void	ft_lstprint_env(void *content);

// pipe.c
void	perror_exit(char *str, int status);
int		pipe_execute(t_list *mini_list, t_list **env);

// redir.c
void	redir_in(t_token *redir);
void	redir_out(char *file);
void	check_heredoc(t_list *redir);
void	redir_append(char *file);
void	check_redir(t_list *redir);

// utils.c
int		split_size(char **split);
char	**env_to_char(t_list *env);

// child.c
void	child_process(t_pipex *pipex, t_mini *curr_mini, int list_size, int i);

// parent.c
void	parent_process(t_pipex *pipex, int list_size, int i);

#endif
