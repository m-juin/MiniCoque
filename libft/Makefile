# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                  +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 13:38:40 by gpasquet          #+#    #+#              #
#    Updated: 2023/02/03 15:01:43 by gpasquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	clang	

NAME	= 	libft.a

INDI	=	\033[38;5;99m

CFLAGS	= 	-Wall -Wextra -Werror

SRCS	=	./src/string/ft_split.c			\
			./src/string/ft_strdup.c		\
			./src/string/ft_strndup.c		\
			./src/string/ft_strrchr.c		\
			./src/string/ft_strcmp.c		\
			./src/string/ft_strncmp.c		\
			./src/string/ft_striteri.c		\
			./src/string/ft_strtrim.c		\
			./src/string/ft_strmapi.c		\
			./src/string/ft_strchr.c		\
			./src/string/ft_strlcat.c		\
			./src/string/ft_strlcpy.c		\
			./src/string/ft_strjoin.c		\
			./src/string/ft_strjoin_f.c		\
			./src/string/ft_str_mega_join.c \
			./src/string/ft_substr.c		\
			./src/string/ft_strnstr.c		\
			./src/string/ft_strlen.c		\
			./src/string/ft_strfindchr.c	\
			./src/memory/ft_memchr.c		\
			./src/memory/ft_calloc.c		\
			./src/memory/ft_memmove.c		\
			./src/memory/ft_memcmp.c		\
			./src/memory/ft_bzero.c			\
			./src/memory/ft_memset.c		\
			./src/memory/ft_memcpy.c		\
			./src/conversion/ft_atoi.c 		\
			./src/conversion/ft_atoll.c 	\
			./src/conversion/ft_itoa.c		\
			./src/char/ft_isalnum.c			\
			./src/char/ft_isdigit.c			\
			./src/char/ft_isalpha.c			\
			./src/char/ft_toupper.c			\
			./src/char/ft_isascii.c			\
			./src/char/ft_tolower.c			\
			./src/char/ft_isprint.c			\
			./src/list/ft_lstnew.c			\
 			./src/list/ft_lstadd_front.c	\
			./src/list/ft_lstsize.c			\
			./src/list/ft_lstlast.c			\
			./src/list/ft_lstadd_back.c		\
			./src/list/ft_lstdelone.c		\
			./src/list/ft_lstclear.c		\
			./src/list/ft_lstiter.c			\
			./src/list/ft_lstmap.c			\
			./src/print/ft_putstr_fd.c		\
			./src/print/ft_putchar_fd.c		\
			./src/print/ft_putendl_fd.c		\
			./src/print/ft_putnbr_fd.c		\
			./src/print/ft_puthexa_fd.c		\
			./src/print/ft_putptr_fd.c		\
			./src/print/ft_printf_fd.c		\
			./src/gnl/get_next_line.c		\
			./src/gnl/get_next_line_utils.c	
			
OBJS= 	${SRCS:%.c=%.o}

RM		=	rm -f

${NAME}: ${OBJS}
	@ar rc ${NAME} ${OBJS}
	@printf "${INDI}libft compiled          \n\033[00m"

.c.o:
	@printf "Compiling libft .c to .o \r"
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	$(NAME)
	
clean:
	@n=1; \
	for file in $(OBJS); do \
		if test -e $$file; then \
			if [ $$n -eq 1 ]; then \
				printf "Cleaning libft .o files \n"; \
			fi; \
			n=$$((n + 1)); \
			rm $$file; \
		fi \
	done

fclean:	clean
	@n=1; \
	if test -e ${NAME}; then \
		if [ $$n -eq 1 ]; then \
			printf "Cleaning libft.a\n"; \
		fi; \
		n=$$((n + 1)); \
		rm ${NAME}; \
	fi

re:	fclean all

.PHONY: all clean fclean re
