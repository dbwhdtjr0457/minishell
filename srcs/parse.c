/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:32:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/27 14:29:13 by joyoo            ###   ########.fr       */
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

t_list	*make_token(char *line)
{
	t_list	*token_list;
	int		*lexer_arr;

	token_list = 0;
	lexer_arr = (int *)ft_calloc(ft_strlen(line) + 1, sizeof(int));
	// 한글자씩 읽으면서 각 char에 대한 정보 저장
	lexer(line, lexer_arr);
	// word와 space 분리
	make_token_list(&token_list, line, lexer_arr);
	free(lexer_arr);
	return (token_list);
}

t_mini	*parsing(char *line, t_list *env)
{
	t_list	*token_list;
	t_mini	*cmd_list;

	cmd_list = 0;
	token_list = make_token(line);
	// 환경변수 치환
	// $가 붙어 있을 경우 ' '안에 있을 경우를 제외하고 env 목록에 있는 변수로 변경
	token_list = change_to_env(token_list, env);
	// printf("change env\n");
	// ft_lstiter(token_list, print_word_in_list);
	// 따옴표 제거
	token_list = split_quote(token_list);
	// printf("del quote env\n");
	// ft_lstiter(token_list, print_word_in_list);
	// syntax 체크
	// 한번에 실행할 token끼리 묶어서 t_split에 저장
	cmd_list = token_comb(token_list);
	ft_lstclear_token(&token_list);
	// printf("\nredir\n");
	// ft_lstiter(cmd_list->redir, print_split_in_list);
	// printf("\nparsed\n");
	// ft_lstiter(cmd_list->parsed, print_split_in_list);
	// ft_lstclear_parsed(&cmd_list);
	//system("leaks --list minishell");
	return (cmd_list);
}
// 따옴표 안닫혔을 떄 처리 필요, 에러가 나!!
