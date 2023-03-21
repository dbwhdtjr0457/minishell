/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:34:18 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/21 14:17:57 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	make_env(t_list **env, char **envp)
{
	int		i;
	char	**tmp;
	int		shlvl;
	char	*tmp_shlvl;

	i = 0;
	*env = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		if (!tmp[1])
			append_str(&tmp, "");
		ft_lstadd_back(env, ft_lstnew(tmp));
		i++;
	}
	tmp_shlvl = get_env("SHLVL", *env);
	shlvl = ft_atoi(tmp_shlvl) + 1;
	free(tmp_shlvl);
	tmp_shlvl = ft_itoa(shlvl);
	set_env("SHLVL", tmp_shlvl, env);
	free(tmp_shlvl);
	ft_lstremove_if(env, "OLDPWD", ft_strncmp);
}

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
			ft_free(tmp[1]);
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
		ft_free(tmp2);
		env = env->next;
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

void	ft_lstremove_if(t_list **lst, void *data_ref, int (*cmp)())
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *lst;
	prev = 0;
	while (tmp)
	{
		if (!cmp(((char **)tmp->content)[0], data_ref, ft_strlen(data_ref) + 1))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*lst = tmp->next;
			free_split(tmp->content);
			ft_free(tmp);
			break ;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
