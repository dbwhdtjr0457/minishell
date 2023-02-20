/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:32:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/20 15:12:49 by joyoo            ###   ########.fr       */
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
t_list	*comb_token(t_list **token_list)
{
	t_list	*token;
	t_list	*res;
	t_split	*split;
	char	**tmp;

	res = 0;
	token = *token_list;
	while (token)
	{
		tmp = 0;
		if (((t_token *)(token->content))->type == PIPE_T)
		{
			split = new_split
				(ft_split(((t_token *)(token->content))->token, ' '),
					((t_token *)(token->content))->type);
			ft_lstadd_back(&res, ft_lstnew(split));
		}
		// 리다이렉션일 경우 type이 3 ~ 6
		else if (((t_token *)(token->content))->type >= 3
			&& ((t_token *)(token->content))->type <= 6)
		{
			if (((t_token *)(token->next)) &&
				((t_token *)(token->next->content))->type == WORD_T)
			{
				append(&tmp, ((t_token *)(token->content))->token);
				append(&tmp, ((t_token *)(token->next->content))->token);
				split = new_split(tmp, ((t_token *)(token->content))->type);
				ft_lstadd_back(&res, ft_lstnew(split));
				token = token->next;
			}
			// else 리다이렉션 뒤에 word token이 나오지 않을 경우 에러 처리 필요 또는 리다이렉션만 나올경우(뒤에가 널일 경우)
		}
		//파이프나 리다리렉션이 나오지 않을 경우 == word 일 경우
		// 파이프나 리다이렉션이 나올 때까지 뒤에 연결
		else
		{
			append(&tmp, ((t_token *)(token->content))->token);
			while (((t_token *)(token->next)) &&
				(((t_token *)(token->next->content))->type == WORD_T ||
				((t_token *)(token->next->content))->type == SPACE_T))
			{
				token = token->next;
				if (((t_token *)(token->content))->type != SPACE_T)
					append(&tmp, ((t_token *)(token->content))->token);
			}
			split = new_split(tmp, ((t_token *)(token->content))->type);
			ft_lstadd_back(&res, ft_lstnew(split));
		}
		token = token->next;
	}
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
	//split_word = change_to_env(split_word, env);
	// 한번에 실행할 token끼리 묶어서 t_split에 저장
	cmd_list = comb_token(&token_list);
	// ft_lstiter(cmd_list, print_split_in_list);
	ft_lstclear_token(&token_list, free);
	(void)cmd_list;
	(void)env;
	return (cmd_list);
}
