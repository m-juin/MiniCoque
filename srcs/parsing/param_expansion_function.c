/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_function.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:10:41 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/18 17:35:21 by gpasquet         ###   ########.fr       */
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
			token->token = ft_substr(input, 0, i);
	}
	token->token_type = token_identifier(token->token[i]);
}

static void	assign_def(t_token *token, char *var, char *input, t_env_var *env)
{
	t_env_var	*tmp_env;
	char		**exp_args;
	char		*tmp_s;
	int			i;

	i = 0;
	tmp_env = get_env(env, var);
	if (tmp_env && tmp_env->value)
		token->token = ft_strdup(tmp_env->value);
	else
	{
		exp_args = malloc(sizeof(char *) * 3);
		if (!exp_args)
			return ;
		exp_args[0] = ft_strdup("export");
		tmp_s = ft_strjoin(var, "=");
		while (input[i] && input[i] != '}')
			i++;
		if (!input[i])
			exp_args[1] = ft_strdup(tmp_s);
		else
			tmp_s = ft_strjoin(tmp_s, ft_substr(input, 0, i));
		exp_args[1] = ft_strdup(tmp_s);
		exp_args[2] = NULL;
		free(tmp_s);
		export(env, exp_args);
		token->token = ft_strdup(ft_substr(input, 0, i));
	}	
	token->token_type = token_identifier(token->token[i]);
}

static void	display_err(t_token *token, char *var, char *input, t_env_var *env)
{
	t_env_var	*tmp;
	char		*msg;
	int			i;

	i = 0;
	tmp = get_env(env, var);
	if (tmp && tmp->value)
		token->token = ft_strdup(tmp->value);
	else
	{
		msg = ft_strjoin("minicoque: ", var);
		if (!msg)
		{
			token->token = NULL;
			return ;
		}	
		if (input[i] == '}')
		{
			msg = ft_strjoin(msg, ": parameter null or not set");
			if (!msg)
			{
				token->token = NULL;
				return ;
			}
		}
		else
		{
			while (input[i] && input[i] != '}')
				i++;
			msg = ft_strjoin(msg, ft_strjoin(": ", ft_substr(input, 0, i)));
		}
		token->token = ft_strdup(msg);
		free(msg);
	}
}

static void	alt_val(t_token *token, char *var, char *input, t_env_var *env)
{
	t_env_var	*tmp;
	int			i;

	i = 0;
	tmp = get_env(env, var);
	if (tmp && tmp->value)
	{
		while (input[i] && input[i] != '}')
			i++;
		token->token = ft_substr(input, 0, i);
	}
	else
		token->token = ft_strdup("");
}

static int	search_colons(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '}')
	{
		if (input[i] == ':')
			return (1);
		i++;
	}
	return (0);
}

static void	subnstring_var(t_token *token, char *var, char *input, t_env_var *env)
{
	int			i;
	int			start;
	int			len;
	t_env_var	*var_node;

	var_node = get_env(env, var);
	if (!var_node || !var_node->name)
	{
		token->token = ft_strdup("");
		return ;
	}
	i = 0;
	while (input[i] != ':')
		i++;
	start = ft_atoi(ft_substr(input, 0, i));
	i++;
	while (input[i] && input[i] != '}')
		i++;
	len = ft_atoi(ft_substr(input, start + 1, i));
	token->token = ft_substr(var_node->value, start, len);
}

static void	substr_var(t_token *token, char *var, char *input, t_env_var *env)
{
	int			i;
	int			len;
	int			start;
	t_env_var	*var_node;

	var_node = get_env(env, var);
	if (!var_node || !var_node->name)
	{
		token->token = ft_strdup("");
		return ;
	}
	i = 0;
	if (search_colons(input) == 1)
		subnstring_var(token, var, input, env);
	while (input[i] && input[i] != '}')
		i++;
	start = ft_atoi(ft_substr(input, 0, i));
	if (start < 0)
		token->token = ft_strdup(var_node->value);
	else
	{
		len = ft_strlen(var_node->value) - start;
		token->token = ft_substr(var_node->value, start, len);
	}
}

void	bracket_var(t_token *token, char *input, t_env_var *env)
{
	int			i;
	t_env_var	*var;	

	i = 0;
	while (input[i] && input[i] != '}')
	{
		if (input[i] == ':')
		{
			if (input[i + 1] == '-')
			{
				use_def(token, ft_substr(input, 0, i), &input[i + 2], env);
				return ;
			}
			if (input[i + 1] == '=')
			{
				assign_def(token, ft_substr(input, 0, i), &input[i + 2], env);
				return ;
			}
			if (input[i + 1] == '?')
			{
				display_err(token, ft_substr(input, 0, i), &input[i + 2], env);
				return ;
			}
			if (input[i + 1] == '+')
			{
				alt_val(token, ft_substr(input, 0, i),
					&input[i + 2], env);
				return ;
			}
			else
			{
				substr_var(token, ft_substr(input, 0, i), &input[i + 1], env);
				return ;
			}
		}
		i++;
	}
	if (input[i] == '}')
	{
		var = get_env(env, ft_substr(input, 0, i));
		if (!var || !var->name)
		{	
			token->token = ft_strdup("");
			return ;
		}
		token->token = ft_strdup(var->value);
	}
	else
		token->token = ft_substr(input - 2, 0, i + 2);
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
