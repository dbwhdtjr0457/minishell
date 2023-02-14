/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:01:08 by jihylim           #+#    #+#             */
/*   Updated: 2022/07/09 15:05:17 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		s1_len;
	int		i;

	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	dst = (char *)malloc(sizeof(char) * s1_len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
