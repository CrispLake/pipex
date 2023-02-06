/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:07:52 by emajuri           #+#    #+#             */
/*   Updated: 2023/02/06 15:26:13 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_vars(t_vars *vars)
{
	vars->count = 1;
	vars->fd_in = 0;
	vars->fd_out = 0;
	vars->pids = NULL;
}

int	fork_error(char **cmd, t_vars *vars, int commands)
{
	perror("Error forking in main");
	free(cmd);
	free(vars->pids);
	close(vars->fd_in);
	close(vars->fd_out);
	if (vars->count < commands)
		close(vars->new[0]);
	exit(-1);
}

void	wait_all(int *pids, int cmd_count)
{
	int	wstatus;
	int	i;

	i = 0;
	wstatus = 0;
	while (i <= cmd_count)
	{
		waitpid(pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
		{
			if (WEXITSTATUS(wstatus) == -1)
			{
				free(pids);
				exit(-1);
			}
		}
		i++;
	}
	free(pids);
}

int	first_checks(int argc, t_vars *vars)
{
	if (argc < 5)
	{
		ft_printf("Too little arguments\n");
		return (-1);
	}
	init_vars(vars);
	vars->pids = ft_calloc(argc - 3, sizeof(int));
	if (!vars->pids)
	{
		perror("Error in ft_calloc");
		return (-1);
	}
	if (pipe(vars->new))
	{
		free(vars->pids);
		perror("Creating pipe failed in first_checks");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	char	**cmd;

	if (first_checks(argc, &vars))
		return (-1);
	while (vars.count <= argc - 3)
	{
		make_fd(argc - 3, &vars, vars.new, argv);
		cmd = add_filepath(argv, vars.count + 1);
		if (!cmd)
			filepath_error(vars.pids);
		vars.pids[vars.count - 1] = fork();
		if (vars.pids[vars.count - 1] == -1)
			fork_error(cmd, &vars, argc - 3);
		else if (vars.pids[vars.count - 1] == 0)
			child(&vars, vars.new, cmd, argc - 3);
		parent(&vars, cmd);
	}
	wait_all(vars.pids, vars.count - 2);
	return (0);
}
