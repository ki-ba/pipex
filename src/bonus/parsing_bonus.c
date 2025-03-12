/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:58:25 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/10 12:28:27 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * @brief returns the basename of the filename passed as parameter.
 * @brief ie `/usr/bin/ls` -> `ls`.
 * @param str the filename.
 * @returns the basename of `str`.
 */
char	*basename(char str[])
{
	char	*last_slash;
	char	*basename;

	basename = NULL;
	if (!ft_str_is_non_empty(str))
		return (NULL);
	last_slash = ft_strrchr(str, '/');
	if (!last_slash)
		last_slash = str;
	basename = ft_substr(last_slash, (last_slash[0] == '/'),
			ft_strlen(last_slash));
	return (basename);
}
