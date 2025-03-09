/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:47:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 16:37:30 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 *	@brief opens the relevant infile and outfile and stores their
 *	@brief file descriptors in `pipex`.
 *	@brief if a `here_doc` is used, creates a tmp file to store the data.
 *	@param pipex the structure to store the file descriptors in.
 *	@param argc the number of arguments the program was called with.
 *	@param argv the arguments the program was called with.
 *	@param here_doc whether a here document is being used or not.
*/
int	set_files(t_pipex *pipex, int argc, char *argv[], t_bool here_doc)
{
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	if (pipex->infile < 0)
		perror(argv[1]);
	if (pipex->outfile < 0)
		perror(argv[argc - 1]);
	if (pipex->outfile < 0 || pipex->infile < 0)
		ft_clean_exit(pipex, EXIT_FAILURE);
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	t_bool;
	int		i;

	set_files(&pipex, argc, argv, 0);
	i = 2;
	if (argc != 5)
		return (usage());
	dup2(pipex.infile, STDIN_FILENO);
	create_linked_child(&pipex, argv[i++], env, 0);
	dup2(pipex.outfile, STDOUT_FILENO);
	create_linked_child(&pipex, argv[argc - 2], env, 1);
	ft_clean_exit(&pipex, EXIT_SUCCESS);
	return (0);
}
