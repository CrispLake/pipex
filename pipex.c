/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:07:52 by emajuri           #+#    #+#             */
/*   Updated: 2023/01/31 17:40:07 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	make_fd(int commands, t_vars *vars, int *old, char **argv)
{
	int	file1;
	int	file2;
	int	old0;
	int old1;

	old0 = old[0];
	old1 = old[1];
	if (vars->count != 1 && vars->count != commands)
	{
		if (pipe(vars->new))
		{
			exit (-1);
		}
	}
	if (vars->count == 1)
	{
		file1 = open(argv[vars->count], O_RDONLY);
		vars->fd_in = dup(file1);
		close(file1);
		vars->fd_out = dup(old1);
		close(old1);
		vars->new[0] = old0;
	}
	else if (vars->count < commands)
	{
		vars->fd_in = dup(old0);
		close(old0);
		vars->fd_out = dup(vars->new[1]);
		close(vars->new[1]);
	}
	else
	{
		vars->fd_in = dup(old0);
		close(old0);
		file2 = open(argv[commands + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		vars->fd_out = dup(file2);
		close(file2);
	}
	return (0);
}

void	init_vars(t_vars *vars)
{
	vars->count = 1;
	vars->fd_in = 0;
	vars->fd_out = 0;
}

void	child(t_vars *vars, int new[2], char **cmd, int commands)
{
	extern char	**environ;

	dup2(vars->fd_in, 0);
	dup2(vars->fd_out, 1);
	close(vars->fd_in);
	close(vars->fd_out);
	if (vars->count < commands)
		close(new[0]);
	execve(cmd[0], cmd + 1, environ);
	free(cmd);
	exit(-1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	char	**cmd;
	int		pid;
	int		wstatus;

	init_vars(&vars);
	if (pipe(vars.new))
	{
		perror("Creating pipe failed in main");
		exit(-1);
	}
	while (vars.count <= argc - 3)
	{
		make_fd(argc - 3, &vars, vars.new, argv);
		cmd = add_filepath(argv, vars.count + 1);
		pid = fork();
		if (pid == -1)
		{
			perror("Error forking in main");
			free(cmd);
			close(vars.fd_in);
			close(vars.fd_out);
			if (vars.count < argc - 3)
				close(vars.new[0]);
			exit (-1);
		}
		else if (pid == 0)
			child(&vars, vars.new, cmd, argc - 3);
		wait(&wstatus);
		close(vars.fd_in);
		close(vars.fd_out);
		if (WIFEXITED(wstatus))
		{
			if (WEXITSTATUS(wstatus) == -1)
			{
				perror("Error in executing command");
				exit(-1);
			}
		}
		vars.count++;
	}
	free(cmd);
	return (0);
}
