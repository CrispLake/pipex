/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:51:26 by emajuri           #+#    #+#             */
/*   Updated: 2023/01/31 16:26:05 by emajuri          ###   ########.fr       */
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
} t_vars;

char	**split_quote(const char *str, int delim);
char	**add_filepath(char **argv, int cmd_i);

#endif
