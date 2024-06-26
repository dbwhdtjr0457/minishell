/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_comb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:50:47 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/21 14:18:25 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// char ** 형에 char * 추가해주는 함수
// res = {"hello"}가 있으면 res = {"hello", "world"} 처럼 뒤에 연결
void	append_str(char ***res, char *str)
{
	int		len;
	int		i;
	char	**tmp;
	char	**new;

	len = 0;
	i = -1;
	tmp = *res;
	if (tmp)
	{
		while (tmp[len])
			len++;
	}
	new = malloc((len + 2) * sizeof(char *));
	while (++i < len)
		new[i] = ft_strdup(tmp[i]);
	new[len] = ft_strdup(str);
	new[len + 1] = 0;
	i = 0;
	while (i < len)
		ft_free(tmp[i++]);
	ft_free(tmp);
	*res = new;
}

static void	mini_init(t_mini **mini)
{
	(*mini) = (t_mini *)malloc(sizeof(t_mini));
	(*mini)->parsed = 0;
	(*mini)->redir = 0;
}

static t_list	*free_mini_res(t_mini *mini, t_list *res)
{
	free_mini(mini);
	ft_lstclear_mini(&res);
	return (0);
}

// 연관있는 토큰끼리 합쳐주는 함수
// t_list *res의 content에 t_split 형태로 저장한 후 반환
// 인자로 받아온 token_list 는 free해줘야 함
t_list	*token_comb(t_list *lst)
{
	t_mini	*mini;
	t_list	*res;

	res = 0;
	while (lst)
	{
		mini_init(&mini);
		while (lst && !is_pipe(lst))
		{
			if (is_space(lst))
				;
			else if (is_redir(lst))
			{
				if (!comb_redir(&lst, &(mini->redir)))
					return (free_mini_res(mini, res));
			}
			else
				append_str(&mini->parsed, ((t_token *)(lst->content))->token);
			lst = lst->next;
		}
		ft_lstadd_back(&res, ft_lstnew(mini));
		if (lst && is_pipe(lst))
			lst = lst->next;
	}
	return (res);
}
