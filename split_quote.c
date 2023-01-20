/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:48:18 by emajuri           #+#    #+#             */
/*   Updated: 2023/01/20 14:44:01 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

const char	*strlen_delim(const char *str, int *full_len, int delim)
{
	while (*str != delim && *str)
	{
		str++;
		(*full_len)++;
	}
	return (str);
}

int	word_count(const char *str, int *full_len, int delim)
{
	int	count;
	int	quote;

	count = 0;
	*full_len = 0;
	while (*str)
	{
		while (*str == delim)
			str++;
		if (*str)
			count++;
		if (*str == '\"' || *str == '\'')
		{
			quote = *str;
			str++;
			str = strlen_delim(str, full_len, quote);
			str++;
		}
		else
			str = strlen_delim(str, full_len, delim);
	}
	return (count);
}

const char	*write_data2(const char *str, int *strlen)
{
	int	quote;

	quote = *str;
	str++;
	strlen_delim(str, strlen, quote);
	return (str);
}

void	write_data(const char *str, char **ptr, int words, int delim)
{
	char	*tmp;
	int		i;
	int		strlen;

	tmp = (char *)(ptr + words);
	i = 0;
	while(words-- > 1)
	{
		ptr[i] = tmp;
		strlen = 0;
		while (*str == delim)
			str++;
		if (*str == '\"' || *str == '\'')
			str = write_data2(str, &strlen);
		else
			strlen_delim(str, &strlen, delim);
		ft_strlcpy(ptr[i++], str, strlen + 1);
		if (*str == '\"' || *str == '\'')
			str++;
		str += strlen + 1;
		tmp += strlen + 1;
	}
	ptr[i] = NULL;
}

char **split_quote(const char *str, int delim)
{
	char	**ptr;
	int		full_len;
	int		words;

	words = (word_count(str, &full_len, delim) + 1);
	ptr = ft_calloc(words * sizeof(char *) + \
			((words - 1) + full_len) * sizeof(char), 1);
	if (!ptr)
	{
		perror("Malloc failed in split_quote");
		return (NULL);
	}
	write_data(str, ptr, words, delim);
	return (ptr);
}
