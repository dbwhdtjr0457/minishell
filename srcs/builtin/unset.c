/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:00:32 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/14 17:33:07 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

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

	fork_check(&pid);
	if (pid == 0)
	{
		check_redir(mini->redir);
		exit(0);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		g_status = ((g_status & 0xff00) >> 8);
		if (g_status != 0)
			return (1);
		tmp = mini->parsed;
		i = 0;
		while (tmp[++i])
			ft_lstremove_if(env, tmp[i], ft_strncmp);
		return (1);
	}
	return (0);
}
