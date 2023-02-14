# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihylim <jihylim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 16:03:53 by jihylim           #+#    #+#              #
#    Updated: 2022/12/10 17:52:12 by jihylim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM      = rm -f
SRCS    = ft_isalpha.c \
		  ft_isdigit.c \
		  ft_isalnum.c \
		  ft_isascii.c \
		  ft_isprint.c \
		  ft_strlen.c \
		  ft_memset.c \
		  ft_bzero.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_strchr.c \
		  ft_strrchr.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_strnstr.c \
		  ft_atoi.c \
		  ft_calloc.c \
		  ft_strdup.c \
		  ft_strncmp.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_itoa.c \
		  ft_strmapi.c \
		  ft_striteri.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c
BONS    = ft_lstnew.c \
		  ft_lstadd_front.c \
		  ft_lstsize.c \
		  ft_lstlast.c \
		  ft_lstadd_back.c \
		  ft_lstdelone.c \
		  ft_lstclear.c \
		  ft_lstiter.c \
		  ft_lstmap.c
OBJS	= $(SRCS:.c=.o)
OBJB	= $(BONS:.c=.o)

ifdef	WITH_BONUS
		OBJ_ALL = ${OBJS} ${OBJB}
else
		OBJ_ALL = ${OBJS}
endif

all 	: 	$(NAME)

$(NAME) : 	$(OBJ_ALL)
			ar rcs ${NAME} $(OBJ_ALL) 

bonus 	:
			make WITH_BONUS=1 all

.c.o	:
			$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean	:
			${RM} $(OBJS) $(OBJB)

fclean	: clean
			${RM} $(NAME)

re 		: 
			make fclean
			make all

.PHONY: all bonus clean fclean re
