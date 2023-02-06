/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_n_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:09:32 by emajuri           #+#    #+#             */
/*   Updated: 2023/02/06 15:14:50 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_error(char **cmd)
{
	free(cmd);
	perror("Error in child");
	exit(-1);
}

void	child(t_vars *vars, int new[2], char **cmd, int commands)
{
	extern char	**environ;

	free(vars->pids);
	if (dup2(vars->fd_in, 0) == -1)
		child_error(cmd);
	if (dup2(vars->fd_out, 1) == -1)
		child_error(cmd);
	if (close(vars->fd_in) == -1)
		child_error(cmd);
	if (close(vars->fd_out) == -1)
		child_error(cmd);
	if (vars->count < commands)
		close(new[0]);
	execve(cmd[0], cmd + 1, environ);
	free(cmd);
	exit(-1);
}

void	parent(t_vars *vars, char **cmd)
{
	free(cmd);
	if (close(vars->fd_in) == -1)
	{
		free(vars->pids);
		perror("Error in parent");
		exit(-1);
	}
	if (close(vars->fd_out) == -1)
	{
		free(vars->pids);
		perror("Error in parent");
		exit(-1);
	}
	vars->count++;
}
