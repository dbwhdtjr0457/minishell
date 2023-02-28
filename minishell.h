/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:20:14 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/28 00:27:42 by jihylim          ###   ########.fr       */
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
	char	**cmd_list;
	char	**path_list;
	char	*cmd_path;
	char	*file1;
	char	*file2;
	int		new_pipe[2];
	int		old_pipe[2];
	pid_t	*pid;
	int		argc;
	char	**argv;
	char	**envp;
	int		heredoc;
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
t_list	*change_to_env(t_list *token_list, t_list *env);

// lexer.c
void	lexer(const char *line, int *arr);

// parse.c
void	print_word_in_list(void *content);
t_list	*make_token(char *line);
t_list	*parsing(char *line, t_list *env);

// is_type.c
int		is_redir(t_list *lst);
int		is_pipe(t_list *lst);
int		is_word(t_list *lst);
int		is_space(t_list *lst);
int		is_double(t_list *lst);

// token_comb.c
t_list	*split_quote(t_list *lst);
t_list	*token_comb(t_list *token_list);

// token_list.c
t_token	*new_token(char *input, int type);
void	make_token_list(t_list **split_word, char *line, int *arr);

// make_env.c
void	make_env(t_list **env, char **envp);

// execute.c
int		split_size(char **split);
int		execute(t_mini *mini, t_list **env);

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
int		pipe_execute(t_mini *mini, t_list **env, int pipe_num);
void	check_redir(t_list *redir);

// main.c
char	**env_to_char(t_list *env);

#endif
