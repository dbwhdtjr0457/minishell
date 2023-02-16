/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:32:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/16 21:34:41 by jihylim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
int	is_word(char c)
{

}
*/

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

void	lexer(const char *line, int *arr)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		j = 0;
		if (line[i] == '\"')
			arr[i] = QUOTE_DOUBLE;
		else if(line[i] == '\'')
			arr[i] = QUOTE_SINGLE;
		else if (line[i] == '<')
		{
			arr[i] = REDIR_L;
		}
		else if (line[i] == '>')
			arr[i] = REDIR_R;
		else if (line[i] == '|')
			arr[i] = PIPE_TOKEN;
		else if (line[i] == ' ')
			arr[i] = SPACE_TOKEN;
		else if (line[i] == '$')
			arr[i] = DOLLAR_TOKEN;
		else
			arr[i] = WORD_TOKEN;
		i++;
	}
	//i = 0;
	//while (arr[i])
	//{
	//	printf("%d ", arr[i]);
	//	i++;
	//}
	//printf("\n");
}

t_list	*parsing(char *line)
{
	int	*lexer_arr;

	lexer_arr = (int *)ft_calloc(ft_strlen(line) + 1, sizeof(int));
	// 한글자씩 읽으면서 각 char에 대한 정보 저장
	lexer(line, lexer_arr);
	return (0);
}
