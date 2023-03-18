# ----------------------------- ANSI CODE ----------------------------- #
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

# ------------------------------- FLAGS ------------------------------- #
NAME			=	minishell

CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -g

LIBFT			=	./libft/libft.a
READLINE		=	$(shell brew --prefix readline)

COMFILE_FLAGS	=	-l readline -L $(READLINE)/lib \
					-l ft -L libft
OBJ_FLAGS 		=	-I $(READLINE)/include \
					-I include \
					-I libft \
					-I gnl

# ------------------------------ SOURCES ------------------------------ #
SRCS_DIR		=	./srcs
SRCS_FILES		=	main.c
SRCS			=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

BUILTIN_DIR		=	./srcs/builtin
BUILTIN_FILES	=	cd.c \
					echo.c \
					env.c \
					exit.c \
					export.c \
					pwd.c \
					unset.c
BUILTIN_SRCS	=	$(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES))

EXECUTE_DIR		=	./srcs/execute
EXECUTE_FILES	=	child.c \
					execute.c \
					heredoc.c \
					parent.c \
					pipe.c \
					redir.c
EXECUTE_SRCS	=	$(addprefix $(EXECUTE_DIR)/, $(EXECUTE_FILES))

PARSE_DIR		=	./srcs/parse
PARSE_FILES		=	parse.c \
					change_to_env.c \
					change_to_env_utils.c \
					is_type_1.c \
					is_type_2.c \
					lexer.c \
					make_token_list.c \
					print_syn_error.c \
					quote_join.c \
					split_env.c \
					token_comb.c \
					token_comb_redir.c \
					token_utils.c
PARSE_SRCS		=	$(addprefix $(PARSE_DIR)/, $(PARSE_FILES))

SETTING_DIR		=	./srcs/setting
SETTING_FILES	=	print_ascii.c \
					signal.c \
					terminal.c
SETTING_SRCS	=	$(addprefix $(SETTING_DIR)/, $(SETTING_FILES))

UTILS_DIR		=	./srcs/utils
UTILS_FILES		=	env_utils.c \
					print_error_exe.c \
					free_env.c \
					free_parsed.c \
					ft_free.c \
					print_error.c \
					print_list.c
UTILS_SRCS		=	$(addprefix $(UTILS_DIR)/, $(UTILS_FILES))

GNL_DIR			=	./gnl
GNL_FILES		=	get_next_line.c \
					get_next_line_utils.c
GNL_SRCS		=	$(addprefix $(GNL_DIR)/, $(GNL_FILES))

# ------------------------------- c. o ------------------------------- #
OBJS_DIR		=	./objs
OBJS			=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o) \
					$(BUILTIN_SRCS:$(BUILTIN_DIR)/%.c=$(OBJS_DIR)/%.o) \
					$(EXECUTE_SRCS:$(EXECUTE_DIR)/%.c=$(OBJS_DIR)/%.o) \
					$(PARSE_SRCS:$(PARSE_DIR)/%.c=$(OBJS_DIR)/%.o) \
					$(SETTING_SRCS:$(SETTING_DIR)/%.c=$(OBJS_DIR)/%.o) \
					$(UTILS_SRCS:$(UTILS_DIR)/%.c=$(OBJS_DIR)/%.o) \
					$(GNL_SRCS:$(GNL_DIR)/%.c=$(OBJS_DIR)/%.o) \

# ------------------------------ MAKE -------------------------------- #

all:			$(NAME)

# ==================================================================== #
$(OBJS_DIR):
				@echo "\n"
				@mkdir $@

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c
				@echo $(GREEN) "Compiling... " $< $(EOC) $(LINE_DEL)
				@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@ -MMD

$(OBJS_DIR)/%.o	: $(BUILTIN_DIR)/%.c
				@echo $(GREEN) "Compiling... " $< $(EOC) $(LINE_DEL)
				@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@ -MMD

$(OBJS_DIR)/%.o	: $(EXECUTE_DIR)/%.c
				@echo $(GREEN) "Compiling... " $< $(EOC) $(LINE_DEL)
				@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@ -MMD

$(OBJS_DIR)/%.o	: $(PARSE_DIR)/%.c
				@echo $(GREEN) "Compiling... " $< $(EOC) $(LINE_DEL)
				@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@ -MMD

$(OBJS_DIR)/%.o	: $(SETTING_DIR)/%.c
				@echo $(GREEN) "Compiling... " $< $(EOC) $(LINE_DEL)
				@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@ -MMD

$(OBJS_DIR)/%.o	: $(UTILS_DIR)/%.c
				@echo $(GREEN) "Compiling... " $< $(EOC) $(LINE_DEL)
				@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@ -MMD

$(OBJS_DIR)/%.o	: $(GNL_DIR)/%.c
				@echo $(GREEN) "Compiling... " $< $(EOC) $(LINE_DEL)
				@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@ -MMD
# ==================================================================== #

$(NAME):		$(OBJS_DIR) $(OBJS)
				@echo $(GREEN) "          Making mocha shells...\n" $(EOC)
				@make bonus -C ./libft
				@$(CC) $(CFLAGS) $(COMFILE_FLAGS) -o $(NAME) $(OBJS) $(LIBFT)
				@echo $(YELLOW) "\n===========================================\n" $(EOC)
				@echo $(YELLOW) "        << MochaShell is made! >>\n" $(EOC)

clean:
				@make clean -C libft
				@$(RM) $(OBJS_DIR)
				@echo $(RED) "        Object file is removed!\n" $(EOC)

fclean: 		clean
				@make fclean -C libft
				@$(RM) $(NAME) -MMD
				@echo $(RED) "        MochaShell is removed!\n\n" $(EOC)

re:
				@make fclean
				@make all

-include $(OBJS:.o=.d)

.PHONY:		all clean fclean re
