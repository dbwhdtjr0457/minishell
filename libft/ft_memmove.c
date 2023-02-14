/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:06:33 by jihylim           #+#    #+#             */
/*   Updated: 2022/07/15 13:51:23 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*ret_dst;
	unsigned char	*ret_src;

	i = 0;
	ret_dst = (unsigned char *)dst;
	ret_src = (unsigned char *)src;
	if (dst == src || len == 0)
		return (dst);
	if (src < dst)
	{
		while (len--)
			ret_dst[len] = ret_src[len];
	}
	else if (dst < src)
	{
		while (i < len)
		{
			ret_dst[i] = ret_src[i];
			i++;
		}
	}
	return (dst);
}
