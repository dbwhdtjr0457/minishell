/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:46 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/16 04:45:32 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstprint(void *content)
{
	char	**tmp;

	tmp = (char **)content;
	write(1, tmp[0], ft_strlen(tmp[0]));
	write(1, "=", 1);
	write(1, tmp[1], ft_strlen(tmp[1]));
	write(1, "\n", 1);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;

	(void)ac;
	(void)av;
	make_env(&env, envp);
	ft_lstiter(env, ft_lstprint);
	write(1, "ok\n", 3);
	return (0);
}
