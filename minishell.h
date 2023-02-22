/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:20:14 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/22 15:14:02 by jihylim          ###   ########.fr       */
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

enum e_token{
	QUOTE_DOUBLE = 1,
	QUOTE_SINGLE,
	REDIR_LL,
	REDIR_L,
	REDIR_RR,
	REDIR_R,
	PIPE_T,
	SPACE_T,
	DALLOR_T,
	WORD_T
};

typedef struct s_split{
	int		type;
	char	**split;
}	t_split;

typedef struct s_token{
	int		type;
	char	*token;
}	t_token;

// free.c
void	free_split(char **split);
void	free_token(void	*content);
void	ft_lstclear_token(t_list **lst);
void	free_parsed(void *content);
void	ft_lstclear_parsed(t_list **lst);
void	ft_lstclear_env(t_list **lst);

// change_to_env.c
t_list	*change_to_env(t_list **token_list, t_list *env);

// lexer.c
void	lexer(const char *line, int *arr);

// parse.c
t_list	*parsing(char *line, t_list *env);

// token_comb.c
t_list	*token_comb(t_list *token_list);

// token_list.c
t_token	*new_token(char *input, int type);
void	make_token_list(t_list **split_word, char *line, int *arr);

// make_env.c
void	make_env(t_list **env, char **envp);

//minishell.c
int		minishell(t_list *parsed, t_list **env);

// execute.c
int		split_size(char **split);
int		execute(t_list *parsed, t_list **env);

// builtin_1.c
int		ft_echo(t_list *parsed);
int		ft_pwd(t_list *parsed);
int		ft_env(t_list *parsed, t_list *env);
int		ft_exit(t_list *parsed, t_list *env);
int		ft_cd(t_list *parsed, t_list **env);
int		ft_export(t_list *parsed, t_list **env);
int		ft_unset(t_list *parsed, t_list **env);

// env_utils.c
char	*get_env(char *key, t_list *env);
void	set_env(char *key, char *value, t_list **env);

// t_list_utils.c
void	ft_lstprint_input(void *content);
void	ft_lstprint_env(void *content);

#endif
