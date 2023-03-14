/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:13:39 by joyoo             #+#    #+#             */
/*   Updated: 2023/03/14 19:12:04 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

void	perror_exit(char *str, int status)
{
	perror(str);
	exit(status);
}

void	ft_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		perror_exit("fork error", 1);
}

void	ft_open(int fd)
{
	if (fd == -1)
		perror_exit("open error", 1);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		perror_exit("dup2 error", 1);
}
