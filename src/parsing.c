/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:58:25 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/04 14:17:26 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_non_empty(char str[])
{
	return (str && str[0]);
}

char	*basename(char str[])
{
	size_t	i;
	char	*last_slash;
	char	*basename;

	i = 0;
	basename = NULL;
	last_slash = ft_strrchr(str, '/');
	if (!last_slash)
		last_slash = str;
	basename = ft_substr(last_slash, (last_slash[0] == '/'),
			ft_strlen(last_slash));
	return (basename);
}

char	**tokenize(char str[])
{
	int		i;
	char	**tokens;

	tokens = ft_split(str, ' ');
	i = 0;
	while (tokens[i])
	{
		tokens[i] = ft_split(tokens[i], ' ');
		++i;
	}
	return (tokens);
}
