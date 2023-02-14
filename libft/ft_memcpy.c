/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:10:53 by jihylim           #+#    #+#             */
/*   Updated: 2022/07/14 20:22:37 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ret_dst;
	unsigned char	*ret_src;

	i = 0;
	ret_dst = (unsigned char *)dst;
	ret_src = (unsigned char *)src;
	if (src != dst)
	{	
		while (i < n)
		{
			ret_dst[i] = ret_src[i];
			i++;
		}
	}
	return (dst);
}
