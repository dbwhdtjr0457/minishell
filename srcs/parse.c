/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:32:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/20 18:53:25 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 한글자씩 while 돌면서 읽기
// ", ' 체크
// 환경변수 해석
// 공백 분리
// pipe 분리
// > >> < << 분리
// 문자 토큰 분리
// 문자 토큰 중 연속된 항목 합치기
// 공백 토큰 제거

// parsing 문법 체크
void	print_word_in_list(void *content)
{
	t_token	*word;

	word = (t_token *)content;
	printf("token: %s type : %d\n", word->token, word->type);
}

void	print_split_in_list(void *content)
{
	t_split	*word;
	int		i;

	i = 0;
	word = (t_split *)content;
	printf("출력 : ");
	while (word->split[i])
		printf("	split: %s type : %d\n", word->split[i++], word->type);
}

// split_word를 받아서 하나씩 순회
// split_word->content 하나씩 보면서
// split_word->content->token 의 내용을 확인
// token 한글자씩 보는데

// $가 붙어 있으면 $나올 때까지 자르기
// $a$b 형태로 들어오면 $a $b 로 자른 이후에 변경,

t_list	*change_to_env(t_list *token_list, t_list *env)
{
	t_list	*res;

	res = 0;
	while (token_list)
	{
		printf("here %s\n", ((t_token *)(token_list->content))->token);
		//to_env(split_word->content, env);
		token_list = token_list->next;
	}
	//printf("%s\n", ((t_token *)lst->content)->token);
	(void)env;
	return (res);
}

t_list	*parsing(char *line, t_list *env)
{
	int		*lexer_arr;
	t_list	*token_list;
	t_list	*cmd_list;

	lexer_arr = (int *)ft_calloc(ft_strlen(line) + 1, sizeof(int));
	token_list = 0;
	cmd_list = 0;
	// 한글자씩 읽으면서 각 char에 대한 정보 저장
	lexer(line, lexer_arr);
	// word와 space 분리
	make_token_list(&token_list, line, lexer_arr);
	free(lexer_arr);
	// 환경변수 치환
	// $가 붙어 있을 경우 ' '안에 있을 경우를 제외하고 env 목록에 있는 변수로 변경
	//token_list = change_to_env(token_list, env);
	// 따옴표 제거 
	// syntax 체크
	// 한번에 실행할 token끼리 묶어서 t_split에 저장
	cmd_list = comb_token(token_list);
	ft_lstiter(cmd_list, print_split_in_list);
	ft_lstclear_token(&token_list, free);
	(void)cmd_list;
	(void)env;
	return (cmd_list);
}
