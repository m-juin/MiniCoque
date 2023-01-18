/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicoque.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:31:55 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/18 14:42:46 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINICOQUE_H
# define MINICOQUE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <ft_boolean.h>
# include "../libft/include/libft.h"

# define BLANK 0
# define LITERAL 1 
# define PIPE 2 
# define S_QUOTE 3 
# define D_QUOTE 4 
# define BRACKET 5
# define PARENTHESIS 6
# define DOLLAR 7

typedef struct s_token {
	char			*token;
	int				token_type;
}	t_token;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	int					declared;
	int					index;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_minicoque
{
	t_env_var	*env_var;
}	t_minicoque;

/*	echo.c	*/

int			echo(char **args);

/*	env.c	*/

int			env();

/*	export.c	*/

int			export(t_env_var *env, char **args);
void		replace_value(t_env_var *env, char *path);

/*	unset.c	*/

int			unset(t_env_var *env, char **args);

/*	pwd.c	*/

int			pwd(void);

/*	cd.c	*/

int			cd(t_env_var *env, char **args);

/*	exit.c	*/

void		ft_exit(int ret);

/*	t_env_utils.c */

t_env_var	*create_env(char *path);
void		ft_env_add_back(t_env_var **lst, t_env_var *new);
t_env_var	*get_env(t_env_var *lst, char *path);
int			get_env_size(t_env_var *env);

/*	env_last_error	*/

int			last_error(int get, int error);

/*	lexer.c	*/

t_token		*lexer(char *av, t_env_var *env);
int			token_identifier(int c);

/*	token_utils.c	*/

void		free_token(t_token **token_tab);
t_token		**init_tokentab(int token_nb);

/*	param_expansion_functions.c	*/

void		doll_management(t_token *token, char *input, t_env_var *env);
#endif
