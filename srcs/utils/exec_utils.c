/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:05:39 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/23 15:06:03 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	ft_exec(char **splitted, t_env_var *env)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		execve(get_cmds(splitted[0], env_to_array(env)), splitted, env_to_array(env));
	else
		waitpid(pid, &status, 0);
}

void	ft_execute(t_minicoque *data, t_btree *tree)
{
	if (ft_strcmp(tree->right->tab_str[0], "exit") == 0)
		ft_exit(tree->right->tab_str, data);
	else if (ft_strcmp(tree->right->tab_str[0], "echo") == 0)
		echo(tree->right->tab_str);
	else if (ft_strcmp(tree->right->tab_str[0], "env") == 0)
		env(data->env_var, tree->right->tab_str);
	else if (ft_strcmp(tree->right->tab_str[0], "export") == 0)
		export(data->env_var, tree->right->tab_str);
	else if (ft_strcmp(tree->right->tab_str[0], "unset") == 0)
		unset(data->env_var, tree->right->tab_str);
	else if (ft_strcmp(tree->right->tab_str[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(tree->right->tab_str[0], "cd") == 0)
		cd(data->env_var, tree->right->tab_str);
	else
		ft_exec(tree->right->tab_str, data->env_var);
}
