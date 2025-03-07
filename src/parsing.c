/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:58:25 by kbarru            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/06 11:07:05 by kbarru           ###   ########lyon.fr   */
=======
/*   Updated: 2025/03/06 19:54:17 by kbarru           ###   ########lyon.fr   */
>>>>>>> a465a365f14d2eb642ed1442c9d3166b52cd1756
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_non_empty(char str[])
{
	return (str && str[0]);
}

char	*basename(char str[])
{
	char	*last_slash;
	char	*basename;

	basename = NULL;
	last_slash = ft_strrchr(str, '/');
	if (!last_slash)
		last_slash = str;
	basename = ft_substr(last_slash, (last_slash[0] == '/'),
			ft_strlen(last_slash));
	return (basename);
}

<<<<<<< HEAD
/* char	**tokenize(char str[])
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
} */
=======
// char	**tokenize(char str[])
// {
// 	int		i;
// 	char	**tokens;

// 	tokens = ft_split(str, ' ');
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		tokens[i] = ft_split(tokens[i], ' ');
// 		++i;
// 	}
// 	return (tokens);
// }
>>>>>>> a465a365f14d2eb642ed1442c9d3166b52cd1756
