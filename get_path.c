/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:22:30 by emajuri           #+#    #+#             */
/*   Updated: 2023/02/06 15:29:11 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*test_paths(char *path, char *cmd)
{
	char	*str;
	char	*str2;
	int		cmd_i;
	int		flag;

	flag = 0;
	cmd_i = 0;
	while (cmd[cmd_i] != ' ' && cmd[cmd_i] != '\0')
	{
		cmd_i++;
		if (cmd[cmd_i] == '\0')
			flag = 1;
	}
	cmd[cmd_i] = '\0';
	str = ft_strjoin(path, "/");
	str2 = ft_strjoin(str, cmd);
	free(str);
	if (access(str2, F_OK))
	{
		free(str2);
		str2 = NULL;
	}
	if (!flag)
		cmd[cmd_i] = ' ';
	return (str2);
}

char	*get_path(char *cmd, int i)
{
	extern char	**environ;
	char		**paths;
	char		*path;

	while (ft_strncmp(environ[i], "PATH=", 5) && environ[i])
		i++;
	if (!environ[i])
		return (NULL);
	paths = split_quote((environ[i]) + 5, ':');
	if (!paths)
		return (NULL);
	path = NULL;
	i = 0;
	while (paths[i] && path == NULL)
		path = test_paths(paths[i++], cmd);
	if (paths[i] == NULL)
	{
		free(path);
		path = NULL;
	}
	free(paths);
	return (path);
}

char	**add_filepath(char **argv, int cmd_i)
{
	char	*tmp;
	char	*full;
	char	**cmd;
	char	*path;

	tmp = get_path(argv[cmd_i], 0);
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, " ");
	free(tmp);
	if (!path)
		return (NULL);
	full = ft_strjoin(path, argv[cmd_i]);
	free(path);
	if (!full)
		return (NULL);
	cmd = split_quote(full, ' ');
	free(full);
	return (cmd);
}

void	filepath_error(int *pids)
{
	free(pids);
	ft_printf("Command not found\n");
	exit(-1);
}
