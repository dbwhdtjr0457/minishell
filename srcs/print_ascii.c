/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:02:09 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/13 14:07:27 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	print_ascii(void)
{
	int		fd;
	char	*line;

	fd = open("./title/ascii.txt", O_RDONLY);
	if (!fd)
	{
		ft_putstr_fd("error\n", 2);
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		ft_putstr_fd(line, 1);
		free(line);
		line = get_next_line(fd);
	}
	write(1, "\n", 1);
	free(line);
	close(fd);
}
