/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:25:39 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/16 20:57:21 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_space(t_list *lst)
{
	if (((t_token *)(lst->content))->type == SPACE_T)
		return (1);
	return (0);
}

int	is_dollar(t_list *lst)
{
	if (((t_token *)(lst->content))->type == DOLLAR_T)
		return (1);
	return (0);
}

int	is_word(t_list *lst)
{
	if (((t_token *)(lst->content))->type == WORD_T)
		return (1);
	return (0);
}
