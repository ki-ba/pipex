/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:47:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/08 17:56:31 by kbarru           ###   ########lyon.fr   */
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
	if (here_doc == TRUE)
	{
		pipex->tmp_filename = create_random_str();
		pipex->infile = open(pipex->tmp_filename, O_CREAT | O_WRONLY, 0644);
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	}
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	}
	if (pipex->infile < 0)
		perror(argv[1]);
	if (pipex->outfile < 0)
		perror(argv[argc - 1]);
	if (pipex->outfile < 0 || pipex->infile < 0)
		exit(EXIT_FAILURE);
	return (0);
}

/*
 *	@brief reads lines from stdin until `delimiter` is entered.
 *	@brief writes the data to a temporary file.
 *	@param pipex the data structure containing the file descriptor
 *	@param of the temp file.
 *	@param delimiter the delimiter indicating end of entry.
*/
void	here_doc(t_pipex *pipex, char *delimiter)
{
	char	*buf;
	char	*delimiter_nl;

	delimiter_nl = ft_strdup(delimiter);
	heap_add_suffix("\n", &delimiter_nl);
	ft_putstr_fd("here_doc>", 1);
	buf = get_next_line(STDIN_FILENO);
	while (buf && ft_strncmp(buf, delimiter_nl, ft_strlen(delimiter_nl)))
	{
		write(pipex->infile, buf, ft_strlen(buf));
		ft_putstr_fd("here_doc>", 1);
		buf = get_next_line(STDIN_FILENO);
	}
	free(delimiter_nl);
	close(pipex->infile);
	pipex->infile = open(pipex->tmp_filename, O_RDONLY);
	if (pipex->infile < 0)
		unlink(pipex->tmp_filename);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	int		here_doc_bool;
	int		i;

	here_doc_bool = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	set_files(&pipex, argc, argv, (ft_strncmp(argv[1], "here_doc", 9) == 0));
	i = 2 + here_doc_bool;
	if ((here_doc_bool && argc < 6) || argc < 5)
		return (usage());
	else if (here_doc_bool)
		here_doc(&pipex, argv[2]);
	dup2(pipex.infile, STDIN_FILENO);
	while (i < argc - 2)
		create_linked_child(argv[i++], env, 0);
	dup2(pipex.outfile, STDOUT_FILENO);
	create_linked_child(argv[argc - 2], env, 1);
	ft_clean(&pipex);
	return (0);
}
