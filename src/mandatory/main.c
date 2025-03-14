/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:47:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/14 16:31:49 by kbarru           ###   ########lyon.fr   */
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
void	set_files(t_pipex *pipex, int argc, char *argv[])
{
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->infile < 0)
	{
		perror(argv[1]);
		pipex->infile = open("/dev/null", O_RDONLY);
	}
	if (pipex->outfile < 0)
	{
		perror(argv[argc - 1]);
	}
}

static int	start_wait(t_pipex *pipex, pid_t pid_1, pid_t pid_2)
{
	int	status;

	if (waitpid(pid_1, &status, 0) == -1)
		ft_clean_exit(pipex, EXIT_FAILURE);
	if (waitpid(pid_2, &status, 0) == -1)
		ft_clean_exit(pipex, EXIT_FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	pid_t	pid1;
	pid_t	pid2;
	int		i;
	int		dup_ret;

	pid1 = 0;
	pid2 = 0;
	if (argc != 5)
		ft_clean_exit(NULL, usage());
	set_files(&pipex, argc, argv);
	i = 2;
	dup_ret = dup2(pipex.infile, STDIN_FILENO);
	close(pipex.infile);
	if (dup_ret == -1)
		ft_clean_exit(&pipex, EXIT_FAILURE);
	pid1 = create_linked_child(&pipex, argv[i++], env, 0);
	dup_ret = dup2(pipex.outfile, STDOUT_FILENO);
	close(pipex.outfile);
	if (dup_ret == -1)
		ft_clean_exit(&pipex, start_wait(&pipex, pid1, 0));
	pid2 = create_linked_child(&pipex, argv[argc - 2], env, 1);
	close(STDOUT_FILENO);
	ft_clean_exit(&pipex, start_wait(&pipex, pid1, pid2));
	return (0);
}
