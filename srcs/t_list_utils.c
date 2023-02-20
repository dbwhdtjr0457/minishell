/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:43:37 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/20 14:53:40 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
