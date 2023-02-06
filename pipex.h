/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:51:26 by emajuri           #+#    #+#             */
/*   Updated: 2023/02/06 15:20:43 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_vars
{
	int	count;
	int	fd_in;
	int	fd_out;
	int	new[2];
	int	*pids;
}	t_vars;

char	**split_quote(const char *str, int delim);
char	**add_filepath(char **argv, int cmd_i);
void	filepath_error(int *pids);
void	make_fd(int commands, t_vars *vars, int *old, char **argv);
void	child(t_vars *vars, int new[2], char **cmd, int commands);
void	parent(t_vars *vars, char **cmd);

#endif
