/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:32:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/27 16:35:42 by jihylim          ###   ########.fr       */
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

int	pipe_check(t_mini *mini)
{
	t_list	*lst;
	t_split	*pre;
	t_split	*cur;
	// int		flag;

	// flag = 0;
	pre = 0;
	lst = mini->parsed;
	if (!lst)
	{
		// 리다이렉션만 들어와도 괜찮은건가?
		// mini 통째로 free 해야하는건지, parsed가 0이면 그냥 넘기는건지 생각해보기
		return (0);
	}
	while (lst)
	{
		cur = (t_split *)lst->content;
		if (cur->type == PIPE_T)
		{
			if (!pre || pre->type != WORD_T || !(lst->next)
				|| (((t_split *)(lst->next->content))->type) != WORD_T)
			{
				printf("pipe error\n");
				ft_lstclear_mini(&mini);
				return (0);
			}
		}
		pre = lst->content;
		lst = lst->next;
	}
	return (1);
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
	if (!token_list)
		return (0);
	// 따옴표 제거
	token_list = split_quote(token_list);
	if (!token_list)
		return (0);
	// printf("del quote env\n");
	// ft_lstiter(token_list, print_word_in_list);
	// 한번에 실행할 token끼리 묶어서 t_split에 저장
	cmd_list = token_comb(token_list);
	ft_lstclear_token(&token_list);
	// syntax 체크
	if (!cmd_list || !pipe_check(cmd_list))
		return (0);
	//printf("\nredir\n");
	//ft_lstiter(cmd_list->redir, print_split_in_list);
	//printf("\nparsed\n");
	//ft_lstiter(cmd_list->parsed, print_split_in_list);
	// system("leaks --list minishell");
	return (cmd_list);
}
// 따옴표 안닫혔을 떄 처리 필요, 에러가 나!!
