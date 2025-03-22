/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:29:28 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/14 16:14:44 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 *	@brief prints correct usage of pipex.
 *	@returns non-zero.
 */
int	usage(void)
{
	ft_printf("usage : ./pipex <infile> <cmd1> <cmd2> <outfile>\n");
	return (1);
}

/*
 *	@brief unlinks the tmp file of name specified in pipex->tmp_filename.
 *	@param pipex the pipex data.
 */
int	ft_clean_exit(t_pipex *pipex, int exit_status)
{
	if (pipex)
	{
		if (pipex->infile > -1)
			close(pipex->infile);
		if (pipex->outfile > -1)
			close(pipex->outfile);
		if(pipex->infile != 0)
			close(0);
		if(pipex->outfile != 1)
			close(1);
		close(2);
		if (pipex->outfile < 0)
			exit(EXIT_FAILURE);
	}
	exit(exit_status);
}
