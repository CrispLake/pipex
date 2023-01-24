/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:51:26 by emajuri           #+#    #+#             */
/*   Updated: 2023/01/24 14:20:59 by emajuri          ###   ########.fr       */
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

enum e_index
{
	FILE1 = 1,
	CMD1 = 2,
	CMD2 = 3,
	FILE2 = 4,
	READ = 0,
	WRITE = 1
};

char	**split_quote(const char *str, int delim);

#endif
