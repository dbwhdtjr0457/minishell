/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyoo <joyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:46 by jihylim           #+#    #+#             */
/*   Updated: 2023/02/18 16:01:15 by joyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_c(int signal)
{
	if (signal == SIGINT)
		write(1, "MochaShell$ \n", 15);
	// 현재까지 입력된 문자열을 str로 바꿔주는 함력
	// 프롬포트를 입력하지 않고 새로운 프롬포트 출력할 때, 프롬포트 비워주기
	rl_replace_line("", 1);
	// rl_display 실행 위해 필요
	rl_on_new_line();
	// readline에 입력된 문자열 다시 출력
	rl_redisplay();
}

void	signal_setting(void)
{
	signal(SIGINT, signal_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_lstprint_input(void *content)
{
	t_token	*token;
	int		i;

	token = (t_token *)content;
	printf("type: %d\n", token->type);
	i = 0;
	while (token->context[i])
	{
		printf("context[i]: %s\n", token->context[i]);
		i++;
	}
}

void	ft_lstprint_env(void *content)
{
	char **tmp;

	tmp = (char **)content;
	printf("%s=%s\n", tmp[0], tmp[1]);
}

t_list	*test_parsing(void)
{
	t_list	*test;
	t_token	*token;

	test = 0;
	// token = (t_token *)malloc(sizeof(t_token));
	// token->type = REDIR_L;
	// token->context = ft_split("<", ' ');
	// ft_lstadd_back(&test, ft_lstnew(token));
	// token = (t_token *)malloc(sizeof(t_token));
	// token->type = WORD_TOKEN;
	// token->context = ft_split("infile", ' ');
	// ft_lstadd_back(&test, ft_lstnew(token));
	// token = (t_token *)malloc(sizeof(t_token));
	// token->type = WORD_TOKEN;
	// token->context = ft_split("cat", ' ');
	// ft_lstadd_back(&test, ft_lstnew(token));
	// token = (t_token *)malloc(sizeof(t_token));
	// token->type = PIPE_TOKEN;
	// token->context = ft_split("|", ' ');
	// ft_lstadd_back(&test, ft_lstnew(token));
	// token = (t_token *)malloc(sizeof(t_token));
	// token->type = WORD_TOKEN;
	// token->context = ft_split("ls -al", ' ');
	// ft_lstadd_back(&test, ft_lstnew(token));
	// token = (t_token *)malloc(sizeof(t_token));
	// token->type = REDIR_R;
	// token->context = ft_split(">", ' ');
	// ft_lstadd_back(&test, ft_lstnew(token));
	// token = (t_token *)malloc(sizeof(t_token));
	// token->type = WORD_TOKEN;
	// token->context = ft_split("outfile", ' ');
	// ft_lstadd_back(&test, ft_lstnew(token));
	token = (t_token *)malloc(sizeof(t_token));
	token->type = WORD_TOKEN;
	token->context = ft_split("pwd", ' ');
	ft_lstadd_back(&test, ft_lstnew(token));
	return (test);
}

int	main(int ac, char **av, char **envp)
{

	char			*line;
	struct termios	term;
	t_list			*parsed;
	t_list			*env;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal_setting();
	make_env(&env, envp);
	while (1)
	{
		line = readline("MochaShell$ ");
		if (!line)
		{
			// ctrl + D 눌렀을 경우
			// 한줄 올리고 커서 12 만큼 앞으로 해서 exit 출력하고 while 빠져나가기
			ft_putstr_fd("\033[1A\033[12Cexit\n", 1);
			break ;
		}
		//아무것도 입력 안하고 엔터만 쳤을 때, history 에 기록 안하도록
		else if (*line == '\0')
			free(line);
		else
		{
			add_history(line);
			parsed = parsing(line);
			(void)parsed;
			parsed = test_parsing();
			// ft_lstiter(parsed, ft_lstprint_input);
			execute(parsed, &env);
			free(line);
			ft_lstclear(&parsed, free);
		}
	}
	(void)ac;
	(void)av;
	return (0);
}
