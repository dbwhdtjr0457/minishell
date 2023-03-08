/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:08:37 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/08 16:47:31 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_word_in_list(void *content)
{
	t_token	*word;

	word = (t_token *)content;
	printf("token: %s type : %d\n", word->token, word->type);
}

void	print_split_in_list(void *content)
{
	t_split	*word;
	int		i;

	i = 0;
	word = (t_split *)content;
	printf("출력 : ");
	while (word->split[i])
		printf("	split: %s type : %d\n", word->split[i++], word->type);
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

void	ft_lstprint_input(void *content)
{
	t_split	*split;
	int		i;

	split = (t_split *)content;
	printf("type: %d\n", split->type);
	i = 0;
	while (split->split[i])
	{
		printf("context[i]: %s\n", split->split[i]);
		i++;
	}
}

void	ft_lstprint_env(void *content)
{
	char	**tmp;

	tmp = (char **)content;
	printf("%s=%s\n", tmp[0], tmp[1]);
}
