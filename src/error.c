/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:24:51 by kbarru            #+#    #+#             */
/*   Updated: 2025/02/05 15:30:30 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void	ft_clean_exit(int errno)
{
	if (errno == 1)
		ft_printf("usage : ./pipex <file1> <cmd1> <cmd2> <file2>\n");
	exit(EXIT_FAILURE);
}
