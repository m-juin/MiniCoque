# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 15:23:54 by mjuin             #+#    #+#              #
#    Updated: 2023/01/18 12:05:25 by mjuin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =	clang

CFLAGS =	-g -Werror -Wextra -Wall -I./includes -I./libft/include

NAME =	MiniCoque

SRC =	srcs/main.c \
		srcs/built-ins/exit.c \
		srcs/built-ins/echo.c \
		srcs/built-ins/env.c \
		srcs/built-ins/export.c \
		srcs/built-ins/unset.c \
		srcs/built-ins/pwd.c \
		srcs/built-ins/cd.c \
		srcs/utils/t_env_utils.c \
		srcs/parsing/lexer.c \
		srcs/parsing/token_utils.c

LIBFT = libft/libft.a

LIBFT_PATH = libft --no-print-directory

OBJ =	${SRC:.c=.o}

all:	${LIBFT} ${NAME}

.c.o:
	@printf "Compiling .c to .o \r"
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
	
$(NAME): ${OBJ}
	@${CC} ${CFLAGS} ${OBJ} ${LIBFT} -lreadline -o ${NAME} 
	@printf '\e[1;37m%-6s\e[m' "Compilation complete"

clean:
	@make clean -C ${LIBFT_PATH}
	@n=1; \
	for file in $(OBJ); do \
		if test -e $$file; then \
			if [ $$n -eq 1 ]; then \
				printf "Cleaning .o files \n"; \
			fi; \
			n=$$((n + 1)); \
			rm $$file; \
		fi \
	done

fclean:	clean
	@make fclean -C ${LIBFT_PATH}
	@n=1; \
	if test -e ${NAME}; then \
		if [ $$n -eq 1 ]; then \
			printf "Cleaning files\n"; \
		fi; \
		n=$$((n + 1)); \
		rm ${NAME}; \
	fi

$(LIBFT):
	@make -C ${LIBFT_PATH}

re:	fclean all

.PHONY:	all clean fclean re libft
