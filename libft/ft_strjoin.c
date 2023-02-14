/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:47:24 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/09 13:47:39 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	while (s1 && s1[j])
		tmp[i++] = s1[j++];
	j = 0;
	while (s1 && s2[j])
		tmp[i++] = s2[j++];
	tmp[i] = '\0';
	return (tmp);
}
