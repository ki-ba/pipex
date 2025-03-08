/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:29:28 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/08 17:14:31 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 *	@brief prints correct usage of pipex.
 *	@returns non-zero.
*/
int	usage(void)
{
	ft_printf("usage : ./pipex <[here_doc LIMITER])");
	ft_printf(" | infile> <cmd1> <cmd2> <outfile>\n");
	return (1);
}

/*
 *	@brief unlinks the tmp file of name specified in pipex->tmp_filename.
 *	@param pipex the pipex data.
*/
void	ft_clean(t_pipex *pipex)
{
	if (pipex->tmp_filename)
		unlink(pipex->tmp_filename);
}

/*
*	@brief frees `n_simple` variables and `n_arr` arrays of strings.
*	@param n_simple the number of simple variables to free.
*	@param n_arr the number of arrays of strings to free.
*	@param ... `n_simple` variables followed by `n_arr` arrays. 
*		If more arguments are provided,
*	they will not be freed.
*/
void	ft_multifree(int n_simple, int n_arr, ...)
{
	int		i;
	va_list	args;
	char	*current_var;
	char	**current_array;

	i = 0;
	while (i < n_simple)
	{
		current_var = va_arg(args, char *);
		free(current_var);
	}
	while (i < n_arr - n_simple)
	{
		current_array = va_arg(args, char **);
		free_arr(current_array);
	}
}
