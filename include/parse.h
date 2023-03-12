/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:12:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/12 23:53:58 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

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

// change_to_env.c
t_list	*change_to_env(t_list *token_list, t_list *env, int flag);

// change_to_env_utils.c
char	*remove_quote(t_list *cur, t_list *env, int flag);

// free_parsed.c
void	free_split(char **split);
void	free_token(void	*content);
void	ft_lstclear_token(t_list **lst);
void	free_mini(t_mini *lst);
void	ft_lstclear_mini(t_list **mini);

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


#endif
