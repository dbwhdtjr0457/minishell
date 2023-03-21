/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:13:11 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/20 23:24:08 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "utils.h"
# include "execute.h"

extern int	g_status;

int		ft_echo(t_mini *mini);
int		ft_pwd(t_mini *mini);
int		ft_env(t_mini *mini, t_list *env, void (*print)(void*));
int		ft_exit(t_mini *mini, t_list *env, int flag);
int		ft_cd(t_mini *mini, t_list **env);
int		ft_export(t_mini *mini, t_list **env);
int		ft_unset(t_mini *mini, t_list **env);

#endif
