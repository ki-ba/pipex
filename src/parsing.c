/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:58:25 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/08 17:13:49 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 *	@brief returns whether `str` is non-null AND non-empty or not.
 *	@param str the string to check.
 *	@returns 1 if `str` is a valid string of length > 0.
 *	@returns 0 otherwise.
*/
int	ft_is_non_empty(char str[])
{
	return (str && str[0]);
}

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
	last_slash = ft_strrchr(str, '/');
	if (!last_slash)
		last_slash = str;
	basename = ft_substr(last_slash, (last_slash[0] == '/'),
			ft_strlen(last_slash));
	return (basename);
}
