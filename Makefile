BLACK			= 	"\033[30m"
GRAY			= 	"\033[30m"
RED				=	"\033[31m"
GREEN			=	"\033[32m"
YELLOW			=	"\033[1;33m"
PURPLE			=	"\033[35m"
CYAN			=	"\033[36m"
WHITE			=	"\033[37m"
EOC				=	"\033[0;0m"
LINE_DEL		=	"\x1b[1A\x1b[M"

NAME			=	minishell

CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -g
# -fsanitize=address

COMFILE_FLAGS	=	-l readline -L ${HOME}/.brew/opt/readline/lib
OBJ_FLAGS 		=	-I ${HOME}/.brew/opt/readline/include

LIBFT			=	./libft/libft.a

SRCS_DIR		=	./srcs
SRCS_FILES		=	main.c \
					free.c \
					make_env.c \
					execute.c \
					builtin_1.c \
					env_utils.c \
					pipe.c \
					print_list.c \
					redir.c \
					utils.c \
					child.c \
					parent.c \
					signal.c \
					terminal.c
SRCS			=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

PARSE_DIR		=	./srcs/parse
PARSE_FILES		=	parse.c \
					change_to_env.c \
					change_to_env_utils.c \
					is_type_1.c \
					is_type_2.c \
					lexer.c \
					print_syn_error.c \
					quote_join.c \
					split_env.c \
					token_comb.c \
					token_comb_redir.c \
					token_list.c \
					token_utils.c
PARSE_SRCS		=	$(addprefix $(PARSE_DIR)/, $(PARSE_FILES))

OBJS_DIR		=	./objs
OBJS			=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o) \
					$(PARSE_SRCS:$(PARSE_DIR)/%.c=$(OBJS_DIR)/%.o) \

LIBFT			=	./libft/libft.a

all:			$(NAME)

$(OBJS_DIR):
				@mkdir -p $@

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c  $(OBJS_DIR)
				@echo $(GREEN) "Compiling... " $< $(EOC) $(LINE_DEL)
				@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

$(OBJS_DIR)/%.o	: $(PARSE_DIR)/%.c $(OBJS_DIR)
				@echo $(GREEN) "Compiling... " $< $(EOC) $(LINE_DEL)
				@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@


$(NAME):		$(OBJS)
				@echo $(GREEN) "      Making mocha shells...\n" $(EOC)
				@make bonus -C ./libft
				@$(CC) $(CFLAGS) $(COMFILE_FLAGS) -o $(NAME) $(OBJS) $(LIBFT)
				@echo $(YELLOW) "\n====================================\n" $(EOC)
				@echo $(YELLOW) "    << MochaShell is made! >>\n" $(EOC)

clean:
				@make clean -C libft
				@$(RM) $(OBJS_DIR)
				@echo $(RED) "      Object file is removed!\n" $(EOC)

fclean: 		clean
				@make fclean -C libft
				@$(RM) $(NAME)
				@echo $(RED) "      MochaShell is removed!\n\n" $(EOC)

re:
				@make fclean
				@make all

-include $(OBJS:.o=.d)

.PHONY:		all clean fclean re
