/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:07:52 by emajuri           #+#    #+#             */
/*   Updated: 2023/01/20 18:15:22 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_pipes(int parent_pipe[2], int child_pipe[2])
{
	if (pipe(parent_pipe) == -1)
	{
		perror("Creating pipe failed in create_pipes");
		return (-1);
	}
	if (pipe(child_pipe) == -1)
	{
		perror("Creating pipe failed in create_pipes");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	**ptr;
	int		parent_pipe[2];
	int		child_pipe[2];

	if (argc != 5)
	{
		ft_printf("Invalid argument count\n");
		return (-1);
	}
	ptr = split_quote(argv[CMD1], ' ');
	if (!ptr)
		return (-1);
	if (create_pipes(parent_pipe, child_pipe))
	{
		free(ptr);
		return (-1);
	}
//	fork_cmd1(ptr, parent_pipe, child_pipe);
	return (0);
}
