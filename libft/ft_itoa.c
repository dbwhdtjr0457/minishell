/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:39:01 by jihylim           #+#    #+#             */
/*   Updated: 2022/07/15 16:15:52 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	itoa_len(long nb)
{
	size_t	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ret;
	long	ln;
	size_t	len;

	ln = n;
	len = itoa_len(ln);
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (0);
	if (ln == 0)
	{
		ret[0] = 48;
		return (ret);
	}
	else if (ln < 0)
	{
		ret[0] = '-';
		ln *= -1;
	}
	while (ln > 0)
	{
		ret[--len] = 48 + (ln % 10);
		ln /= 10;
	}
	return (ret);
}
