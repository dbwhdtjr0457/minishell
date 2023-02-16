NAME			=	minishell

SRCS_DIR		=	./srcs
SRCS_FILES		=	main.c \
					make_env.c
SRCS			=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

LIBFT			=	./libft/libft.a

OBJS			=	$(SRCS:.c=.o)

CC				=	cc

RM				=	rm -f

CFLAGS			=	-Wall -Wextra -Werror


$(NAME):		$(OBJS)
				make bonus -C ./libft
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./libft -lft

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