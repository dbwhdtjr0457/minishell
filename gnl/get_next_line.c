/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:47:12 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/10 15:08:43 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ret_before_enter(char *tmp, char **buffer)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!*tmp)
		return (0);
	while (tmp[len] && tmp[len] != '\n')
		len++;
	if (tmp[len] == '\n')
		len++;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	while (*tmp && *tmp != '\n')
		ret[i++] = *tmp++;
	if (*tmp == '\n')
	{
		ret[i++] = '\n';
		tmp++;
	}
	ret[i] = '\0';
	*buffer = gnl_strjoin(0, tmp);
	return (ret);
}

char	*read_buffer_size(int fd, char *buffer)
{
	char	*tmp;
	int		read_size;

	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (0);
	while (!gnl_strchr(buffer, '\n'))
	{
		read_size = read(fd, tmp, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(tmp);
			tmp = 0;
			return (0);
		}
		else if (read_size == 0)
			break ;
		tmp[read_size] = '\0';
		buffer = gnl_strjoin(buffer, tmp);
	}
	free(tmp);
	tmp = 0;
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*ret;
	char		*tmp;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	tmp = read_buffer_size(fd, buffer);
	if (!tmp)
	{
		free(buffer);
		buffer = 0;
		return (0);
	}
	buffer = 0;
	ret = ret_before_enter(tmp, &buffer);
	if (gnl_strlen(buffer) == 0)
	{
		free(buffer);
		buffer = 0;
	}
	free(tmp);
	tmp = 0;
	return (ret);
}
