NAME			=	minishell

SRCS_DIR		=	./srcs
SRCS_FILES		=	main.c \
					parse.c \
					make_env.c
SRCS			=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

LIBFT			=	./libft/libft.a

OBJS			=	$(SRCS:.c=.o)

CC				=	cc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror

COMFILE_FLAGS 	=	-l readline -L ${HOME}/.brew/opt/readline/lib
OBJ_FLAGS 		=	-I ${HOME}/.brew/opt/readline/include

LIBFT			=	./libft/libft.a

$(NAME):		$(OBJS)
				make bonus -C ./libft
				$(CC) $(CFLAGS) $(COMFILE_FLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
				$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

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
