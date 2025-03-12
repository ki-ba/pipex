/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:29:28 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/10 14:40:06 by kbarru           ###   ########lyon.fr   */
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
		if (pipex->infile > 2)
			close(pipex->infile);
		if (pipex->outfile > 2)
			close(pipex->outfile);
	}
	exit(exit_status);
}
