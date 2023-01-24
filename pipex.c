/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:07:52 by emajuri           #+#    #+#             */
/*   Updated: 2023/01/24 18:25:26 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1)
		close(fd1);
	if (fd2)
		close(fd2);
	if (fd3)
		close(fd3);
	if (fd4)
		close(fd4);
}

char	**add_filename(char **argv, int cmd_i)
{
	char	*filename;
	char	*full;
	char	**cmd;
	char	*save;

	filename = ft_strjoin(argv[0], " ");
	if (!filename)
	{
		perror("Strjoin failed in add_filename");
		return (NULL);
	}
	full = ft_strjoin(filename, argv[cmd_i]);
	free(filename);
	if (!full)
	{
		perror("Strjoin failed in add_filename");
		return (NULL);
	}
	cmd = split_quote(full, ' ');
	save = cmd[0];
	cmd[0] = cmd[1];
	cmd[1] = save;
	free(full);
	return (cmd);
}

int	parent3()
{
/*	int	status;

	free(cmd);
	close_fds(output2[WRITE], input, 0, 0);
	wait(&status);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			parent2(input[WRITE], argv);
		else
		{
			close(input[WRITE]);
			perror("cmd1 returned error");
		}
	}*/
	return (0);
}
int	child(int output[2], int input, char **cmd)
{
	(void)cmd;
	close(output[READ]);
	dup2(input, STDIN_FILENO);
	dup2(output[WRITE], STDOUT_FILENO);
	//execve
	return (0);
}

int	parent2(int input, char **argv)
{
	int		pid;
	int		output[2];
	char	**cmd;

	cmd =  add_filename(argv, CMD2);
	if (!cmd)
	{
		close(input);
		exit(-1);
	}
	if (pipe(output) == -1)
	{
		perror("Creating pipe failed in parent");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		close_fds(input, output[WRITE], output[READ], 0);
	if (pid)
		parent3();
	else
		child(output, input, cmd);
	return (0);
}

int	parent(char **cmd, int input, int output, char **argv)
{
	int	file_fd;
	int	status;
	
	file_fd = open(argv[FILE1], O_RDONLY);
	if (file_fd == -1)
	{
		close_fds(input, output, 0, 0);
		perror("Open failed in parent");
		exit(-1);
	}
	dup2(file_fd, input);
	wait(&status);
	free(cmd);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			parent2(output, argv);
		else
		{
			close(input);
			perror("cmd1 returned error");
			exit(-1);
		}
	}
	return (0);
}

int	forks(char **cmd, int input[2], int output[2], char **argv)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		close_fds(input[WRITE], input[READ], output[WRITE], output[READ]);
		free(cmd);
		perror("Fork failed in forks");
	}
	else if (pid)
	{
		close_fds(input[READ], output[WRITE], 0, 0);
		parent(cmd, input[WRITE], output[READ], argv);
	}
	else
	{
		close_fds(input[WRITE], output[READ], 0, 0);
		dup2(input[READ], STDIN_FILENO);
		dup2(output[WRITE], STDOUT_FILENO);
		//execve
	}
	return (0);
}

int	create_pipes(int input[2], int output[2])
{
	if (pipe(input) == -1)
	{
		perror("Creating pipe failed in create_pipes");
		return (-1);
	}
	if (pipe(output) == -1)
	{
		close_fds(input[READ], input[WRITE], 0, 0);
		perror("Creating pipe failed in create_pipes");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	**cmd;
	int		input[2];
	int		output[2];

	if (argc != 5)
	{
		ft_printf("Invalid argument count\n");
		return (-1);
	}
	cmd = add_filename(argv, CMD1);
	if (!cmd)
		return (-1);
	if (create_pipes(input, output))
	{
		free(cmd);
		return (-1);
	}
	forks(cmd, input, output, argv);
	return (0);
}
