/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:13:39 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/14 17:35:01 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

void	perror_exit(char *str, int status)
{
	perror(str);
	exit(status);
}

void	fork_check(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		perror_exit("fork error", 1);
}

void	open_check(int fd)
{
	if (fd == -1)
		perror_exit("open error", 1);
}

void	dup2_check(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		perror_exit("dup2 error", 1);
}
