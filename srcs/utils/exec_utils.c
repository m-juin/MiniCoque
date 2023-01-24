/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:05:39 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/24 12:20:10 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	ft_exec(char **splitted, t_env_var *env, int fds[2])
{
	int ret;
	int	pid;

	ret = 0;
	pid = fork();
	if (pid == 0)
	{
		if (fds[0] != 0 && fds[0] != -1)
		{
			dup2(fds[0], 0);
			close(fds[0]);
		}
		if (fds[1] != 1 && fds[1] != -1)
		{
			dup2(fds[1], 1);
			close(fds[1]);
		}
		ret = execve(get_cmds(splitted[0], env_to_array(env)), splitted, env_to_array(env));
	}
	else
		wait(NULL);
	return (ret);
}

void	ft_execute(t_minicoque *data, t_btree *tree, int fds[2])
{
	if (ft_strcmp(tree->left->tab_str[0], "exit") == 0)
		ft_exit(tree->right->tab_str, data);
	else if (ft_strcmp(tree->left->tab_str[0], "echo") == 0)
		echo(tree->right->tab_str, fds);
	else if (ft_strcmp(tree->left->tab_str[0], "env") == 0)
		 env(data->env_var, tree->right->tab_str, fds);
	else if (ft_strcmp(tree->left->tab_str[0], "export") == 0)
		export(data->env_var, tree->right->tab_str, fds);
	else if (ft_strcmp(tree->left->tab_str[0], "unset") == 0)
		unset(data->env_var, tree->right->tab_str);
	else if (ft_strcmp(tree->left->tab_str[0], "pwd") == 0)
		pwd(fds);
	else if (ft_strcmp(tree->right->tab_str[0], "cd") == 0)
		cd(data->env_var, tree->right->tab_str);
	else
		ft_exec(tree->right->tab_str, data->env_var, fds);
}

void	last_exec(t_minicoque *data, t_btree *tree, int fds[2])
{
	close(fds[1]);
	fds[1] = -1;
	ft_execute(data, tree, fds);
	close(fds[0]);
}

void	ft_first_exec(t_minicoque *data, t_btree *tree, int fds[2])
{
	int	err;

	err = pipe(fds);
	if (err == -1)
		return ;
	ft_execute(data, tree, fds);
}

void	child_cmd(int fds[2], t_minicoque *data, t_btree *tree)
{
	ft_execute(data, tree, fds);
	close(fds[0]);
	close(fds[1]);
}
