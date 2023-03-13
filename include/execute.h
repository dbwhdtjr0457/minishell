/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:47:16 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/13 14:16:27 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "libft.h"
# include "utils.h"
# include <fcntl.h>

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

// child.c
void	child_process(t_pipex *pipex, t_mini *curr_mini, int list_size, int i);

// execute.c
// int		split_size(char **split);
char	*find_path(char *cmd, t_list *env);
int		builtin(t_mini *mini, t_list **env);
int		execute(t_list *mini_list, t_list **env);

// heredoc.c
int		check_heredoc(t_list *redir);

// parent.c
void	parent_process(t_pipex *pipex, int list_size, int i);

// pipe.c
void	perror_exit(char *str, int status);
int		pipe_execute(t_list *mini_list, t_list **env);

// redir.c
void	redir_in(t_token *redir);
void	redir_out(char *file);
void	redir_append(char *file);
void	check_redir(t_list *redir);

#endif
