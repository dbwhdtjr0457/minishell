/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihylim <jihylim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:32:06 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/18 01:42:09 by jihylim          ###   ########.fr       */
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
void	rexer_redir_check(const char *line, int *arr, int *i, int type)
{
	char	t;

	if (type == REDIR_L)
		t = '<';
	else
		t = '>';
	arr[*i] = type;
	if (line[*i + 1] && line[*i + 1] == t)
	{
		arr[*i] = type - 1;
		arr[*i + 1] = type - 1;
		(*i)++;
	}
}

void	lexer(const char *line, int *arr)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			arr[i] = QUOTE_DOUBLE;
		else if (line[i] == '\'')
			arr[i] = QUOTE_SINGLE;
		else if (line[i] == '<')
			rexer_redir_check(line, arr, &i, REDIR_L);
		else if (line[i] == '>')
			rexer_redir_check(line, arr, &i, REDIR_R);
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
}

void	print_arr(char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
}

t_token	*new_token(char *context, int type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->context = context;
	new->type = type;
	return (new);
}


void	print_lst(void *split_word)
{
	printf("herehe\n");
	printf("content : %s\n",
		((t_token *)((t_list *)split_word)->content)->context);
}

t_token	*new_lsttoken(char *line, int *arr, int *i)
{
	t_token	*res;
	int	start;
	int	type;

	res = 0;
	start = *i;
	type = arr[*i];
if (arr[*i] == WORD_TOKEN || arr[*i] == SPACE_TOKEN || arr[*i] == REDIR_LL || arr[*i] == REDIR_RR)
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
				break;
		}
	}
	//ft_lstadd_back(split_word, ft_lstnew(new_token(ft_substr(line, start, *i - start + 1), WORD_TOKEN)));
	res = new_token(ft_substr(line, start, *i - start + 1), type);
	//printf("content : %s\n", res->context);
	//ft_lstiter(split_word, print_lst);
	//s(void)split_word;
	(void)res;
	return (res);
}

void	split_space_quote(t_list **split_word, char *line, int *arr)
{
	int		i;
	t_token	*to;

	i = 0;
	while (arr[i])
	{
		to = new_lsttoken(line, arr, &i);
		//ft_lstadd_back(split_word, ft_lstnew(new_lsttoken(split_word, line, arr, &i)));
		//printf("content : %p\n",((t_token *)((t_list *)split_word)->content)->context);

//		ft_lstadd_back(split_word, ft_lstnew(to));
		i++;
	}
	(void)to;
	(void)split_word;
	(void)line;
}

t_list	*parsing(char *line)
{
	int		*lexer_arr;
	t_list	**split_word;

	lexer_arr = (int *)ft_calloc(ft_strlen(line) + 1, sizeof(int));
	split_word = 0;
	// 한글자씩 읽으면서 각 char에 대한 정보 저장
	lexer(line, lexer_arr);
	// word와 space 분리
	split_space_quote(split_word, line, lexer_arr);
	(void)split_word;
	return (0);
}
