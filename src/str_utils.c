/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:13:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/08 18:52:04 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
*	@brief adds specified suffix to a `s1` in place-ish.
*	@brief copies s1, adds the suffix, then frees the previous `s1` 
*	@brief and replaces it by the new.
*	@param s1 pointer to the current string.
*	@param suffix the suffix to add.
*	@note will cause a segfault if the string was not allocated on the heap.
*/
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

/*
*	@brief concatenates the first `n` strings passed as parameters.
*	@brief the resulting string is allocated on the heap.
*	@param n the number of strings to concatenate.
*	@param ... the strings to concatenate.
*	@returns the resulting concatenated string.
*	@note passed strings do not need to be allocated on the heap.
*	@note no freeing of said strings is done.
*/
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

/*
 *	@brief checks whether passed string contains only 
 *	@brief alphanumerical characters or not.
 *	@param str the string to check.
 *	@returns TRUE (1) if `str` is alnum,
 *	@returns FALSE (0) otherwise.
*/
t_bool	str_is_alnum(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]))
			return (FALSE);
	}
	return (TRUE);
}

/*
 *	@brief creates a pseudo-random string of `TMP_FILENAME_LENGTH`
 *	@brief length on the heap.
 *	@returns the pseudo-random string.
*/
char	*create_random_str(void)
{
	int		urandom;
	char	*random_str;

	random_str = ft_calloc((TMP_FILENAME_LENGTH + 1), sizeof(char));
	random_str[0] = '\0';
	urandom = open("/dev/urandom", O_RDONLY);
	if (urandom < 0)
		return (NULL);
	while (!random_str[0] || !str_is_alnum(random_str)
		|| ft_strlen(random_str) != TMP_FILENAME_LENGTH)
		read(urandom, random_str, TMP_FILENAME_LENGTH);
	close(urandom);
	return (concat(2, "tmp_", random_str));
}
