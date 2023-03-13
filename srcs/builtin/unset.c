/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:00:32 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/13 16:41:20 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

int	ft_unset(t_mini *mini, t_list **env)
{
	char	**tmp;
	int		i;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		check_redir(mini->redir);
		exit(0);
	}
	else
	{
		waitpid(pid, 0, 0);
		tmp = mini->parsed;
		i = 0;
		while (tmp[++i])
			ft_lstremove_if(env, tmp[i], ft_strncmp);
		g_status = 0;
		return (1);
	}
}
