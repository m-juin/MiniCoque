/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_function.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:10:41 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/18 14:32:35 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	use_def(t_token *token, char *var_name, char *input, t_env_var *env)
{
	t_env_var	*tmp;
	int			i;

	i = 0;
	tmp = get_env(env, var_name);
	if (tmp && tmp->value)
		token->token = ft_strdup(tmp->value);
	else
	{
		while (input[i] && input[i] != '}')
			i++;
		if (!input[i])
			token->token = ft_strdup("");
		else
			token->token = ft_strdup(ft_substr(input, 0, i));
	}
	token->token_type = token_identifier(token->token[i]);
}

static void	assign_def(t_token *token, char *var_name, char *input, t_env_var *env)
{
	t_env_var	*tmp_env;
	char		**exp_args;
	char		*tmp_s;
	int			i;

	i = 0;
	tmp_env = get_env(env, var_name);
	if (tmp_env && tmp_env->value)
		token->token = ft_strdup(tmp_env->value);
	else
	{
		exp_args = malloc(sizeof(char *) * 3);
		if (!exp_args)
			return ;
		exp_args[0] = ft_strdup("export");	
		tmp_s = ft_strjoin(var_name, "=");
		while (input[i] && input[i] != '}')
			i++;
		if (!input[i])
			 exp_args[1] = ft_strdup(tmp_s);
		else
			tmp_s = ft_strjoin(tmp_s, ft_substr(input, 0, i));
		exp_args[1] = ft_strdup(tmp_s);
		exp_args[2] = NULL;
		free(tmp_s);
		free(tmp_env);
		export(env, exp_args);
		token->token = ft_strdup(ft_substr(input, 0, i));
	}	
	token->token_type = token_identifier(token->token[i]);
}
/*
static void	display_err(t_token *token, char *var_name, char *input, t_env_var *env)
{}

static void	alternate_value(t_token *token, char *var_name, char *input, t_env_var *env)
{}

static void	substring_var(t_token *token, char *var_name, char *input, t_env_var *env)
{}
*/
void	bracket_var(t_token *token, char *input, t_env_var *env)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '}')
	{
		if (input[i] == ':')
		{
			if (input[i + 1] == '-')
				use_def(token, ft_substr(input, 0, i), &input[i + 2], env);
			if (input[i + 1] == '=')
				assign_def(token, ft_substr(input, 0, i), &input[i + 2], env);
	/*		if (input[i + 1] == '?')
				display_err(token, ft_substr(input, 0, i), &input[i + 2], env);
			if (input[i + 1] == '+')
				alternate_value(token, ft_substr(input, 0, i), &input[i + 2], env);
			else
				substring_var(token, ft_substr(input, 0, i), &input[i + 2], env);
	*/	}
		i++;
	}
}

void	doll_management(t_token *token, char *input, t_env_var *env)
{
	int			i;
	t_env_var	*tmp;

	i = 0;
	if (input[i] == '{')
		bracket_var(token, input + 1, env);
	else
	{	
		while (input[i])
		{
			if (token_identifier(input[i]) != token_identifier(input[i + 1]))
				break ;
			i++;
		}
		if (input[i])
			i++;
		tmp = get_env(env, ft_substr(input, 0, i));
		if (tmp)
			token->token = ft_strdup(tmp->value);
		else
			token->token = ft_strdup("");
	}
	token->token_type = token_identifier(token->token[0]);
}
