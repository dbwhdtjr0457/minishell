/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:15:58 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/18 16:57:45 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	*ft_strjoin_free(char *s1, char *s2)
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
	ft_free(s1);
	ft_free(s2);
	return (tmp);
}

static char	*change_quote_dollar(t_token *token, t_list *env)
{
	char	*str;
	t_list	*token_list;

	str = ft_substr(token->token, 1, ft_strlen(token->token) - 2);
	if (!str)
		return (0);
	if (!ft_strncmp(str, "\0", ft_strlen(str) + 1))
		return (str);
	token_list = make_token(str, 1);
	ft_free(str);
	token_list = change_to_env(token_list, env, 1);
	if (!token_list)
		return (0);
	str = token_join(token_list);
	ft_lstclear_token(&token_list);
	return (str);
}

// change_dollar
	// token type이 dollar 일 경우 달러 다음에 오는 문자만 잘라서 확인
static char	*change_dollar(t_token *token, t_list *env, int flag)
{
	char	*remove_d;
	char	*res;
	char	*get;
	char	*tmp;

	res = 0;
	remove_d = ft_substr(token->token, 1, ft_strlen(token->token) - 1);
	get = get_env(remove_d, env);
	if (!remove_d || !ft_strncmp(remove_d, "\0", ft_strlen(remove_d) + 1))
		res = ft_strdup("$");
	else if (!ft_strncmp(remove_d, "?", ft_strlen(remove_d) + 1))
	{
		tmp = ft_itoa(g_status);
		res = ft_strdup(tmp);
		ft_free(tmp);
	}
	else if (get)
		res = ft_strdup(get);
	else if (flag)
		res = ft_strdup("");
	else
		res = 0;
	ft_free(get);
	ft_free(remove_d);
	return (res);
}

char	*remove_quote(t_list *cur, t_list *env, int flag)
{
	t_token	*token;
	char	*str;

	token = (t_token *)(cur->content);
	str = 0;
	if (token->type == QUOTE_DOUBLE || (token->type == QUOTE_SINGLE && flag))
	{
		str = change_quote_dollar(token, env);
		if (token->type == QUOTE_SINGLE)
		{
			if (!str)
				str = ft_strdup("''");
			else
				str = ft_strjoin_free(ft_strdup("'"),
						ft_strjoin_free(str, ft_strdup("'")));
		}
	}
	else if (token->type == DOLLAR_T)
		str = change_dollar(token, env, flag);
	else if (token->type == QUOTE_SINGLE)
		str = ft_substr(token->token, 1, ft_strlen(token->token) - 2);
	return (str);
}
