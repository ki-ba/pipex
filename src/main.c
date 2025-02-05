/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:47:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/02/05 15:34:06 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
{
	int		fd1;
	int		fd2;
	char	*str;

	if(argc != 5)
		ft_clean_exit(1);
	while(--argc)
		if (!ft_is_non_empty(argv[argc]))
			ft_clean_exit(1);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open (argv[4], O_RDWR);
	if (fd1 < 0 || fd2 < 0)
	{
		if (fd1 < 0)
			str = argv[1];
		else
			str = argv[4];
		ft_printf("Error : could not open file '%s'\n", str);
		return (1);
	}
		return (0);
}
