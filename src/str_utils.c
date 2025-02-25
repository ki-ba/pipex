/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:13:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/02/25 17:56:04 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heap_add_suffix(const char *suffix, char **s1)
{
	size_t	suffix_len;
	size_t	s1_len;
	size_t	i;
	char	*s1_dup;

	s1_dup = ft_strdup(*s1);
	if (!s1_dup)
		return ;
	suffix_len = ft_strlen(suffix);
	s1_len = ft_strlen(s1_dup);
	free(*s1);
	*s1 = malloc((s1_len + suffix_len + 1) * sizeof(char));
	if (!(*s1))
		return ;
	i = -1;
	while (++i < s1_len)
		(*s1)[i] = s1_dup[i];
	i = -1;
	while (++i < suffix_len)
		(*s1)[s1_len + i] = suffix[i];
	(*s1)[s1_len + suffix_len] = '\0';
	free(s1_dup);
}

void	heap_add_prefix(const char *prefix, char *s2)
{
	size_t	prefix_len;
	size_t	s2_len;
	size_t	i;
	char	*s2_dup;

	i = 0;
	s2_dup = ft_strdup(s2);
	prefix_len = ft_strlen(prefix);
	s2_len = ft_strlen(s2);
	s2 = malloc((prefix_len + s2_len + 1) * sizeof(char));
	if (!s2)
		return ;
	while (i < prefix_len)
	{
		s2[i] = prefix[i];
		++i;
	}
	i = 0;
	while (i < s2_len)
	{
		s2[prefix_len + i] = s2_dup[i];
		++i;
	}
	s2[prefix_len + i] = '\0';
	free(s2_dup);
}

char	*concat(size_t n, ...)
{
	va_list	lst;
	size_t	i;
	char	*string;

	i = 0;
	string = malloc(sizeof(char));
	string[0] = '\0';
	va_start(lst, n);
	while (i < n)
	{
		heap_add_suffix(va_arg(lst, char *), &string);
		++i;
	}
	va_end(lst);
	return (string);
}
