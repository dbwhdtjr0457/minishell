/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:24:59 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/16 14:42:30 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

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

// env_utils.c
void	make_env(t_list **env, char **envp);
char	*get_env(char *key, t_list *env);
void	set_env(char *key, char *value, t_list **env);
char	**env_to_char(t_list *env);
void	ft_lstremove_if(t_list **lst, void *data_ref, int (*cmp)());

// error.c
void	perror_exit(char *str, int status);
void	ft_fork(pid_t *pid);
void	ft_open(int fd);
void	ft_dup2(int fd1, int fd2);

// free_env.c
void	ft_lstclear_env(t_list **lst);

// free_parsed.c
void	free_split(char **split);
void	free_token(void	*content);
void	ft_lstclear_token(t_list **lst);
void	free_mini(t_mini *lst);
void	ft_lstclear_mini(t_list **mini);

// ft_free.c
void	ft_free(void *ptr);

// print_error.c
void	print_error_str(char *s1, char *s2, char *str);

// print_list.c
void	print_word_in_list(void *content);
void	print_mini(void *content);
void	ft_lstprint_env(void *content);
void	ft_lstprint_export(void *content);

#endif
