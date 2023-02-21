/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:32:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/21 20:11:27 by jihylim          ###   ########.fr       */
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

// token_list 받아서 하나씩 순회
// token_list->content 하나씩 보면서
// token_list->content->token 의 내용을 확인
// token 한글자씩 보는데

// quote_env
	// token type이 "" 일 경우, "" 떼고, 안의 내용 공백 또는 $로 나누기
	// change_dallor
	// 치환 후 join으로 담기
// change_dallor
	// token type이 dallor 일 경우 달러 다음에 오는 문자만 잘라서 확인

char	*change_dallor(t_token *token, t_list *env)
{
	char	*remove_d;
	char	*res;
	char	*get;

	res = 0;
	remove_d = ft_substr(token->token, 1, ft_strlen(token->token));
	get = get_env(remove_d, env);
	if (get)
		res = ft_strdup(get);
	else
		res = ft_strdup(token->token);
	free(get);
	free(remove_d);
	return (res);
}

t_list	*change_to_env(t_list **token_list, t_list *env)
{
	t_list	*res;
	t_token	*token;
	char	*change;

	res = *token_list;
	while (*token_list)
	{
		token = (t_token *)((*token_list)->content);
		if (token->type == DALLOR_T)
		{
			change = change_dallor(token, env);
			(*token_list)->content = new_token(change, WORD_T);
			free(token);
		}
		// else if (token->type == QUOTE_DOUBLE)
		// {
		// 	quote_env(token);
		// 	change = change_dallor(token, env);
		// 	token = new_token(change, QUOTE_DOUBLE);
		// }
		// printf("here %s\n", token->token);
		(*token_list) = (*token_list)->next;
	}
// printf("aa : %s\n", ((t_token*)(res)->content)->token);
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
	token_list = change_to_env(&token_list, env);
	ft_lstiter(token_list, print_word_in_list);

	// 따옴표 제거
	// syntax 체크
	// 한번에 실행할 token끼리 묶어서 t_split에 저장
	//cmd_list = token_comb(token_list);
	// ft_lstiter(cmd_list, print_split_in_list);
	ft_lstclear_token(&token_list);

	// system("leaks --list minishell");
	(void)cmd_list;
	(void)env;

	return (0);
}
