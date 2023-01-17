/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicoque.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:31:55 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/17 16:00:24 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../libft/include/libft.h"

#define BLANK 0
#define LITERAL 1 
#define PIPE 2 
#define S_QUOTE 3 
#define D_QUOTE 4 
#define BRACKET 5
#define PARENTHESIS 6
#define DOLLAR 7

typedef struct s_token {
	char			*token;
	int				token_type;
}	t_token;



/*	echo.c	*/

int		echo(char **args);
void	ft_exit(int ret);

/*	lexer.c	*/
t_token	*lexer(char *av);
