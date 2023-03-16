/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:07 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/16 13:53:07 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_error_str(char *s1, char *s2, char *str)
{
	ft_putstr_fd("MochaShell: ", 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	if (str)
		ft_putstr_fd(str, 2);
}
