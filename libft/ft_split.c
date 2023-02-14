/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:34:47 by jihylim           #+#    #+#             */
/*   Updated: 2023/01/06 22:27:38 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cnt_wd(const char *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			cnt++;
			while (*s && !(*s == c))
				s++;
		}
	}
	return (cnt);
}

static char	*put_wd(const char *s, char c)
{
	int		len;
	char	*word;

	len = 0;
	while (s[len] && !(s[len] == c))
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static char	**free_wd(char **s, int i)
{
	while (s[i] && --i >= 0)
	{
		free(s[i]);
		s[i] = 0;
	}
	free(s);
	s = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_calloc(cnt_wd(s, c) + 1, sizeof(char *));
	if (!res)
		return (0);
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s && !(*s == c))
		{
			res[i] = put_wd(s, c);
			if (!res[i])
				free_wd(res, i);
			i++;
			while (*s && !(*s == c))
			s++;
		}
	}
	return (res);
}
