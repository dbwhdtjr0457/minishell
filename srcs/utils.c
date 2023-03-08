/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:08:01 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/07 14:14:29 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

char	**env_to_char(t_list *env)
{
	char	**tmp;
	char	*tmp2;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	i = 0;
	while (env)
	{
		tmp2 = ft_strjoin(((char **)env->content)[0], "=");
		tmp[i] = ft_strjoin(tmp2, ((char **)env->content)[1]);
		free(tmp2);
		env = env->next;
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
