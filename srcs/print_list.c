/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:08:37 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/12 23:54:58 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_word_in_list(void *content)
{
	t_token	*word;

	word = (t_token *)content;
	printf("token: %s type : %d\n", word->token, word->type);
}

void	print_mini(void *content)
{
	t_mini	*mini;
	int		i;

	i = 0;
	mini = (t_mini *)content;
	printf("parsed\n");
	while (mini->parsed && mini->parsed[i])
		printf("출력 : %s\n", mini->parsed[i++]);
	printf("\nredir\n");
	ft_lstiter(mini->redir, print_word_in_list);
	printf("==========================\n\n");
}

void	ft_lstprint_env(void *content)
{
	char	**tmp;

	tmp = (char **)content;
	if (tmp[1] && ft_strncmp(tmp[1], "", ft_strlen(tmp[1])))
		printf("%s=%s\n", tmp[0], tmp[1]);
}

void	ft_lstprint_export(void *content)
{
	char	**tmp;

	tmp = (char **)content;
	printf("declare -x %s", tmp[0]);
	if (tmp[1] && ft_strncmp(tmp[1], "", ft_strlen(tmp[1])))
		printf("=\"%s\"", tmp[1]);
	printf("\n");
}
