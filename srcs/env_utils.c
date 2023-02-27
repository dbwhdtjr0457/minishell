/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:34:18 by joyoo             #+#    #+#             */
/*   Updated: 2023/02/27 16:26:23 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *key, t_list *env)
{
	char	**tmp;
	char	*ret;

	while (env)
	{
		tmp = env->content;
		if (ft_strncmp(tmp[0], key, ft_strlen(tmp[0]) + 1) == 0)
		{
			ret = ft_strdup(tmp[1]);
			return (ret);
		}
		env = env->next;
	}
	return (0);
}

void	set_env(char *key, char *value, t_list **env)
{
	char	**tmp;
	t_list	*tmp_env;

	tmp_env = *env;
	while (tmp_env)
	{
		tmp = tmp_env->content;
		if (!ft_strncmp(tmp[0], key, ft_strlen(key) + 1))
		{
			free(tmp[1]);
			tmp[1] = ft_strdup(value);
			return ;
		}
		tmp_env = tmp_env->next;
	}
	tmp = (char **)malloc(sizeof(char *) * 3);
	tmp[0] = ft_strdup(key);
	tmp[1] = ft_strdup(value);
	tmp[2] = 0;
	ft_lstadd_back(env, ft_lstnew(tmp));
}
