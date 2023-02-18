/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:32:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/18 15:33:49 by jihylim          ###   ########.fr       */
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

t_word	*new_word(char *context, int type)
{
	t_word	*new;

	new = (t_word *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->context = context;
	new->type = type;
	return (new);
}

void	print_word_in_list(void *content)
{
	t_word	*word;

	word = (t_word *)content;
	printf("context: %s type : %d\n", word->context, word->type);
}

t_word	*split_space_quote(char *line, int *arr, int *i)
{
	int		start;
	int		type;

	start = *i;
	type = arr[*i];
	if (arr[*i] == WORD_TOKEN || arr[*i] == SPACE_TOKEN
		|| arr[*i] == REDIR_LL || arr[*i] == REDIR_RR)
	{
		while (arr[*i] == type)
			*i += 1;
		*i -= 1;
	}
	else if (arr[*i] == QUOTE_DOUBLE || arr[*i] == QUOTE_SINGLE)
	{
		*i += 1;
		while (arr[*i] && arr[*i] != type)
		{
			*i += 1;
			if (arr[*i] == type)
				break ;
		}
	}
	return (new_word(ft_substr(line, start, *i - start + 1), type));
}

void	word_lst(t_list **split_word, char *line, int *arr)
{
	int		i;
	t_word	*word;

	i = 0;
	*split_word = 0;
	while (arr[i])
	{
		word = split_space_quote(line, arr, &i);
		ft_lstadd_back(split_word, ft_lstnew(word));
		free(word->context);
		i++;
	}
}

t_list	*parsing(char *line)
{
	int		*lexer_arr;
	t_list	*split_word;

	lexer_arr = (int *)ft_calloc(ft_strlen(line) + 1, sizeof(int));
	split_word = 0;
	// 한글자씩 읽으면서 각 char에 대한 정보 저장
	lexer(line, lexer_arr);
	// word와 space 분리
	word_lst(&split_word, line, lexer_arr);
	free(lexer_arr);
	//write(1, "\n", 1);
	//ft_lstiter(split_word, print_word_in_list);
	//write(1, "\n", 1);
	ft_lstclear(&split_word, free);
	return (0);
}
