# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 15:23:54 by mjuin             #+#    #+#              #
#    Updated: 2023/02/07 11:49:56 by gpasquet         ###   ########.fr        #
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
		srcs/utils/env_last_exit.c \
		srcs/utils/env_clst_utils.c \
		srcs/utils/free_utils.c \
		srcs/utils/exec_utils.c \
		srcs/utils/tree_creation_utils.c \
		srcs/utils/tree_exec_utils.c \
		srcs/utils/individual_exec_utils.c \
		srcs/utils/fd_utils.c \
		srcs/utils/tab_utils.c \
		srcs/utils/get_cmd_utils.c \
		srcs/utils/token_utils.c \
		srcs/utils/parsing_utils.c \
		srcs/utils/counting_utils.c \
		srcs/utils/redirect_parsing_utils.c \
		srcs/utils/heredoc_utils.c \
		srcs/utils/error_utils.c \
		srcs/utils/quotes_parsing_utils.c \
		srcs/utils/pipe_counting_utils.c \
		srcs/functions/ft_execute.c \
		srcs/functions/signals.c \
		srcs/parsing/lexer.c \
		srcs/parsing/param_expansion_function.c \
		srcs/parsing/counting_functions.c \
		srcs/parsing/parsing.c \
		srcs/parsing/quotes_management_functions.c \
		srcs/parsing/redirection_parsing.c \
		srcs/parsing/heredoc_functions.c \
		srcs/parsing/heredoc_pipe_functions.c \
		srcs/parsing/heredoc_fork.c

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
