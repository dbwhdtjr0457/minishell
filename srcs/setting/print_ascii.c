/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:02:09 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/14 17:34:46 by joyoo            ###   ########.fr       */
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
	open_check(fd);
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
