/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicoque.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:31:55 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/17 16:01:49 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../libft/include/libft.h"

typedef struct	s_env_var
{
	char			*name;
	char			*value;
	int				declared;
	int				index;
	struct s_env_var	*next;
}	t_env_var;

typedef struct	s_minicoque
{
	t_env_var	*env_var;
}	t_minicoque;

/*	echo.c	*/

int			echo(char **args);

/*	env.c	*/

int			env();

/*	export.c	*/

int			export(t_env_var *env, char **args);

/*	exit.c	*/

void		ft_exit(int ret);

/*	t_env_utils.c */

t_env_var	*create_env(char *path);
void		ft_env_add_back(t_env_var **lst, t_env_var *new);
t_env_var	*check_env(t_env_var *lst, char *path);