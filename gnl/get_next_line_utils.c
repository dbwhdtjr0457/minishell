/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:47:46 by jihylim           #+#    #+#             */
/*   Updated: 2023/01/19 00:44:08 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	i = 0;
	j = 0;
	if (!s2)
		return (s1);
	tmp = (char *)malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!tmp)
	{
		free(s1);
		s1 = 0;
		return (0);
	}
	while (s1 && s1[j])
		tmp[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		tmp[i++] = s2[j++];
	tmp[i] = '\0';
	free(s1);
	s1 = 0;
	return (tmp);
}
