/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:19:08 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/08 16:36:45 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	@brief frees the array of strings passed as parameter.
	@param arr the array to free.
*/
void	free_arr(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

/*
 *	@brief prints the values of the array of strings passed as parameter.
 *	@param arr the array to print.
*/
void	print_arr(char **arr)
{
	int	i;

	ft_printf("\n\n === ARRAY PRINTING ===\n\n");
	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		ft_printf("%s\n", arr[i]);
	ft_printf("\n\n ==========\n\n");
}

/*
	@brief adds a prefix to a heap string in place.
	@param prefix the prefix to add.
	@param s2 the string to add a prefix to.
*/
void	str_arr_suffix(char **arr, char *suffix)
{
	int	i;

	i = -1;
	while (arr[++i])
		heap_add_suffix(suffix, &(arr[i]));
}

int	get_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		++i;
	return (i);
}

/*
 *	@brief allocates a copy of the array of strings passed as a parameter.
 *	@param arr the array to duplicate.
*/
char	**duplicate_arr(char **arr)
{
	int		i;
	int		size;
	char	**dup;

	i = -1;
	size = get_arr_size(arr);
	dup = malloc(sizeof(char *) * (size + 1));
	while (++i < size)
		dup[i] = ft_strdup(arr[i]);
	dup[i] = 0;
	return (dup);
}
