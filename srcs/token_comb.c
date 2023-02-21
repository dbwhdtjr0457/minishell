/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_comb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:50:47 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/21 21:53:00 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_split	*new_split(char **input, int type)
{
	t_split	*new;

	new = (t_split *)malloc(sizeof(t_split));
	if (!new)
		return (0);
	new->split = input;
	new->type = type;
	return (new);
}

// char ** 형에 char * 추가해주는 함수
// res = {"hello"}가 있으면 res = {"hello", "world"} 처럼 뒤에 연결
void	append(char ***res, char *str)
{
	int		len;
	int		i;
	char	**tmp;
	char	**new;

	len = 0;
	i = -1;
	tmp = *res;
	if (tmp)
	{
		while (tmp[len])
			len++;
	}
	new = malloc((len + 2) * sizeof(char *));
	// 이전 배열 포인터가 가리키는 영역에서 새로운 메모리 영역으로 문자열 포인터들을 복사
	while (++i < len)
		new[i] = strdup(tmp[i]);
	// 새로 추가할 문자열을 새로운 메모리 영역의 마지막에 추가
	new[len] = strdup(str);
	new[len + 1] = 0;
	// 이전 배열 포인터가 가리키는 영역의 메모리 해제
	i = 0;
	while (i < len)
		free(tmp[i++]);
	free(tmp);
	// 배열 포인터를 새로 할당된 메모리 영역의 주소로 업데이트
	*res = new;
}

// 연관있는 토큰끼리 합쳐주는 함수
// t_list *res의 content에 t_split 형태로 저장한 후 반환
// 인자로 받아온 token_list 는 free해줘야 함
t_list	*token_comb(t_list *token_list)
{
	t_token	*token;
	t_list	*res;
	t_split	*split;
	char	**tmp;

	res = 0;
	while (token_list)
	{
		tmp = 0;
		token = (t_token *)(token_list->content);
		if (token->type == PIPE_T)
		{
			split = new_split(ft_split(token->token, ' '), (token->type));
			ft_lstadd_back(&res, ft_lstnew(split));
		}
		// 리다이렉션일 경우 type이 3 ~ 6
		else if (token->type >= 3 && token->type <= 6)
		{
			if (((t_token *)(token_list->next)) &&
				((t_token *)(token_list->next->content))->type == WORD_T)
			{
				append(&tmp, token->token);
				append(&tmp, ((t_token *)(token_list->next->content))->token);
				split = new_split(tmp, token->type);
				ft_lstadd_back(&res, ft_lstnew(split));
				token_list = token_list->next;
			}
			// else 리다이렉션 뒤에 word token이 나오지 않을 경우 에러 처리 필요 또는 리다이렉션만 나올경우(뒤에가 널일 경우)
		}
		//파이프나 리다리렉션이 나오지 않을 경우 == word 일 경우
		// 파이프나 리다이렉션이 나올 때까지 뒤에 연결
		else
		{
			append(&tmp, token->token);
			while (((t_token *)(token_list->next)) &&
				(((t_token *)(token_list->next->content))->type == WORD_T ||
				((t_token *)(token_list->next->content))->type == SPACE_T))
			{
				token_list = token_list->next;
				token = (t_token *)(token_list->content);
				// 공백인 경우  저장하지  않고  넘어가기
				if (token->type != SPACE_T)
					append(&tmp, token->token);
			}
			split = new_split(tmp, token->type);
			ft_lstadd_back(&res, ft_lstnew(split));
		}
		token_list = token_list->next;
	}
	return (res);
}
