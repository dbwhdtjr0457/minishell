/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 03:55:09 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/16 15:01:48 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_env(t_list **env, char **envp)
{
	int		i;
	char	**tmp;

	i = 0;
	*env = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		ft_lstadd_back(env, ft_lstnew(tmp));
		free_split(tmp);
		i++;
	}
}
