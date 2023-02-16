/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:32:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/16 18:57:36 by jihylim          ###   ########.fr       */
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

void	lexer(const char *line, char *arr)
{
	int	i;
	int	j;
	const char	token[10][3] = {"\"", "\'", "<<", "<", ">>", ">", "|", " ", "$"};

	i = 0;
	while (line[i])
	{
		j = 0;
		while (j < 10)
		{
			//if (line[i] == token[j][0])
			//{
	//			if (line [i] == "<" || line[i] == ">")
					// 다음거가 연속으로 나오는지 확인 후 둘다 같은 red로 저장
	//			else
	//				arr[i] = j;
	//	}
			j++;
		}
		i++;
	}
	//printf("%s\n", arr);
	(void)line;
	(void)arr;
}

t_list	*parsing(char *line)
{
	char	*lexer_arr;

	lexer_arr = ft_calloc(ft_strlen(line) + 1, 1);
	// 한글자씩 읽으면서 각 char에 대한 정보 저장
	lexer(line, lexer_arr);
	return (0);
}
