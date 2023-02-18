NAME			=	minishell

CC				=	cc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror

COMFILE_FLAGS 	=	-l readline -L/opt/homebrew/opt/readline/lib
OBJ_FLAGS 		=	-I/opt/homebrew/opt/readline/include

LIBFT			=	./libft/libft.a

SRCS_DIR		=	./srcs
SRCS_FILES		=	main.c \
					free.c \
					make_env.c \
					execute.c \
					builtin_1.c \
					parse.c
SRCS			=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

LIBFT			=	./libft/libft.a

OBJS			=	$(SRCS:.c=.o)

%.o: %.c
				$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				make bonus -C ./libft
				$(CC) $(CFLAGS) $(COMFILE_FLAGS) -o $(NAME) $(OBJS) $(LIBFT)

all:			$(NAME)

clean:
				make clean -C libft
				$(RM) $(OBJS) $(OBJS_BONUS) $(OBJS_GNL)

fclean: 		clean
				make fclean -C libft
				$(RM) $(NAME)

re:
				make fclean
				make all

.PHONY:		all clean fclean re
