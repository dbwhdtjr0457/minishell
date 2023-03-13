/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:32:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/13 20:18:49 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// 한글자씩 while 돌면서 읽기
// ", ' 체크
// 환경변수 해석
// 공백 분리
// pipe 분리
// > >> < << 분리
// 문자 토큰 분리
// 문자 토큰 중 연속된 항목 합치기
// 공백 토큰 제거

t_list	*make_token(char *line, int flag)
{
	t_list	*token_list;
	int		*lexer_arr;

	token_list = 0;
	lexer_arr = (int *)ft_calloc(ft_strlen(line) + 1, sizeof(int));
	lexer(line, lexer_arr);
	make_token_list(&token_list, line, lexer_arr, flag);
	free(lexer_arr);
	return (token_list);
}

static int	pipe_check(t_list *lst)
{
	int		flag;

	flag = -1;
	while (lst)
	{
		if (is_pipe(lst))
		{
			if (flag == -1 || !flag)
				break ;
			flag = 0;
		}
		else if (!is_pipe(lst) && !is_space(lst))
			flag = 1;
		lst = lst->next;
	}
	if (lst || !flag)
	{
		print_syn_error(0, "'|'\n");
		return (0);
	}
	if (flag == -1)
		return (0);
	return (1);
}

// make_token : 입력받은 line을 기준으로 토큰을 나누어 리스트에 저장
// change_to_env : 환경변수 치환
	// $가 붙어 있을 경우 ' '안에 있을 경우를 제외하고 env 목록에 있는 변수로 변경
// quote_join : 따옴포 제거, 스페이스 아닌 토큰들 하나의 str로 붙여서 리스트만들기
// token_comb : 파이프를 기준으로 리다이렉션 끼리, word 끼리 묶어서 저장

t_list	*parsing(char *line, t_list *env)
{
	t_list	*token_list;
	t_list	*cmd_list;

	cmd_list = 0;
	token_list = make_token(line, 0);
	token_list = change_to_env(token_list, env, 0);
	if (!token_list)
		return (0);
	token_list = quote_join(token_list);
	if (!token_list)
		return (0);
	cmd_list = token_comb(token_list);
	if (!cmd_list || !pipe_check(token_list))
	{
		ft_lstclear_token(&token_list);
		ft_lstclear_mini(&cmd_list);
		return (0);
	}
	ft_lstclear_token(&token_list);
	return (cmd_list);
}
