/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:00:50 by emajuri           #+#    #+#             */
/*   Updated: 2023/02/06 15:05:10 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_perror(int *pids)
{
	free(pids);
	perror("Error in dup_fds");
	exit(-1);
}

void	dup_fds(t_vars *vars, int fd1, int fd2)
{
	vars->fd_in = dup(fd1);
	if (vars->fd_in == -1)
		free_perror(vars->pids);
	if (close(fd1) == -1)
		free_perror(vars->pids);
	vars->fd_out = dup(fd2);
	if (vars->fd_out == -1)
		free_perror(vars->pids);
	if (close(fd2) == -1)
		free_perror(vars->pids);
}

void	first_command(t_vars *vars, char *file, int old0, int old1)
{
	int	file1;

	file1 = open(file, O_RDONLY);
	if (file1 == -1)
	{
		perror("Opening file 1 failed");
		close(vars->new[0]);
		close(vars->new[1]);
		exit(-1);
	}
	dup_fds(vars, file1, old1);
	vars->new[0] = old0;
}

void	make_fd(int commands, t_vars *vars, int *old, char **argv)
{
	int	file2;
	int	old0;
	int	old1;

	old0 = old[0];
	old1 = old[1];
	if (vars->count != 1 && vars->count != commands)
		if (pipe(vars->new))
			exit(-1);
	if (vars->count == 1)
		first_command(vars, argv[vars->count], old0, old1);
	else if (vars->count < commands)
		dup_fds(vars, old0, vars->new[1]);
	else
	{
		file2 = open(argv[commands + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file2 == -1)
		{
			perror("Opening file 2 failed");
			close(old[0]);
			exit(-1);
		}
		dup_fds(vars, old0, file2);
	}
}
