/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:32:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/03/05 15:08:19 by jihylim          ###   ########.fr       */
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

void	print_mini(void *content)
{
	t_mini	*mini;
	int		i;

	i = 0;
	mini = (t_mini *)content;
	printf("parsed\n");
	while (mini->parsed && mini->parsed[i])
		printf("출력 : %s\n", mini->parsed[i++]);
	printf("\nredir\n");
	ft_lstiter(mini->redir, print_word_in_list);
	printf("==========================\n\n");
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

int	pipe_check(t_list *lst)
{
	int		flag;

	flag = -1;
	while (lst)
	{
		if (is_pipe(lst))
		{
			if (!flag)
				break ;
			flag = 0;
		}
		else if (!is_pipe(lst) && !is_space(lst))
			flag = 1;
		lst = lst->next;
	}
	if (lst || !flag)
	{
		print_syn_error(0, "'|'|\n");
		return (0);
	}
	// exit 코드 고려할떄 이건 에러 아님
	// 스페이스만 들어왔을 떄 처리한것
	if (flag == -1)
		return (0);
	return (1);
}

t_list	*parsing(char *line, t_list *env)
{
	t_list	*token_list;
	t_list	*cmd_list;

	cmd_list = 0;
	token_list = make_token(line);
	// 환경변수 치환
	// $가 붙어 있을 경우 ' '안에 있을 경우를 제외하고 env 목록에 있는 변수로 변경
	token_list = change_to_env(token_list, env, 0);
	if (!token_list)
		return (0);
	// 따옴표 제거
	// 여기서 따옴표 안에 있는거 분리 안해도 되는거지???
	//token_list = split_quote(token_list);
	//if (!token_list)
	//	return (0);
	//ft_lstiter(token_list, print_word_in_list);
	// 스페이스 아닌 토큰들 하나의 str로 붙여서 token_list 만들기
	token_list = quote_join(token_list);
	//if (!token_list || !pipe_check(token_list))
		//return (0);
	// 한번에 실행할 token끼리 묶어서 t_split에 저장
	cmd_list = token_comb(token_list);
	//ft_lstiter(token_list, print_word_in_list);
	//ft_lstclear_token(&token_list);
	// syntax 체크
	//system("leaks --list minishell");
	if (!cmd_list || !pipe_check(token_list))
	//if (!cmd_list)
	{
		ft_lstclear_token(&token_list);
		ft_lstclear_mini(&cmd_list);
		return (0);
	}
	ft_lstclear_token(&token_list);
	//ft_lstiter(cmd_list, print_mini);
	// system("leaks --list minishell");
	return (cmd_list);
}
//> d -al | ls < <
// ls -al < d > | d
// 따옴표 안닫혔을 떄 처리 필요, 에러가 나!!
