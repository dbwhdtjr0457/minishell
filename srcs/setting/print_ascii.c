/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:02:09 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/14 19:11:57 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setting.h"
#include "utils.h"
#include <fcntl.h>

void	print_ascii(void)
{
	int		fd;
	char	*line;

	fd = open("./title/ascii.txt", O_RDONLY);
	ft_open(fd);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = 0;
		line = get_next_line(fd);
	}
	printf("\n");
	free(line);
	line = 0;
	close(fd);
}
