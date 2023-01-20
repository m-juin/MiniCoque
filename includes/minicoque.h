/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicoque.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:31:55 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/20 16:32:26 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINICOQUE_H
# define MINICOQUE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <ft_boolean.h>
# include <sys/wait.h>
# include "../libft/include/libft.h"

# define BLANK 0
# define LITERAL 1 
# define PIPE 2 
# define S_QUOTE 3 
# define D_QUOTE 4 
# define REDIRECT 5
# define DOLLAR 6
# define NUULL 7
# define PCOLOR "\001\e[0;36m\002"
# define RESET   "\001\e[0m\002"

typedef struct s_token {
	char			*str;
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

/*	env_clst_utils.c	*/

int			get_env_size(t_env_var *env);
char *const	*env_to_array(t_env_var *env);

/*	echo.c	*/

int			echo(char **args);

/*	env.c	*/

int			env();

/*	export.c	*/

int			export(t_env_var *env, char **args);

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
void		replace_value(t_env_var *env, char *path);
t_env_var	*get_env(t_env_var *lst, char *path);

/*	env_last_exit	*/

int			last_exit(t_bool get, int error);

/*	lexer.c	*/

t_token		**lexer(char *av, t_env_var *env);

/*	token_utils.c	*/

void		free_token(t_token **token_tab);
t_token		**init_tokentab(char *input);
void		pipe_token(t_token **token_tab, int *i, int *nb);
void		redirect_token(t_token **token_tab, char *input, int *i, int *nb);

/*	param_expansion_functions.c	*/

char		*doll_management(char *input, t_env_var *env);

/*	param_utils.c	*/

int			typify(int c);
int			digit_str(char *str);

/*	counting_functions.c	*/

int			token_count(char *input);

#endif
