/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:20:14 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/15 22:38:30 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "libft/libft.h"

# define WORD_TOKEN		1
# define CMD_TOKEN 		2
# define OPT_TOKEN		3
# define ARG_TOKEN		4
# define PIPE_TOKEN		5
# define REDIR_TOKEN	6
# define SPACE_TOKEN	7
# define QUOTE_TOKEN	8
# define DOLLAR_TOKEN	9

typedef struct s_token{
	int				type;
	char			context;
	struct s_token	*next;
}	t_token;

// parse.c
t_token	*parsing(char *line);

#endif
