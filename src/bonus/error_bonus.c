/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:29:28 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/14 12:23:20 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
int	ft_clean_exit(t_pipex *pipex, int exit_status)
{
	if (pipex->infile > 2)
		close(pipex->infile);
	if (pipex->outfile > 2)
		close(pipex->outfile);
	if (pipex->tmp_filename)
	{
		unlink(pipex->tmp_filename);
		free(pipex->tmp_filename);
	}
	if (pipex->outfile < 0)
		exit(EXIT_FAILURE);
	exit(exit_status);
}
