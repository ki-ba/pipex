/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:47:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/14 17:10:57 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
 *	@brief opens the relevant infile and outfile and stores their
 *	@brief file descriptors in `pipex`.
 *	@brief if a `here_doc` is used, creates a tmp file to store the data.
 *	@param pipex the structure to store the file descriptors in.
 *	@param argc the number of arguments the program was called with.
 *	@param argv the arguments the program was called with.
 *	@param here_doc whether a here document is being used or not.
 */
void	set_files(t_pipex *pipex, int argc, char *argv[], t_bool here_doc)
{
	pipex->tmp_filename = NULL;
	if (here_doc == TRUE)
	{
		pipex->tmp_filename = ft_strdup("tmp_pipex");
		if (!(pipex->tmp_filename))
			ft_clean_exit(pipex, EXIT_FAILURE);
		pipex->infile = open(pipex->tmp_filename, O_CREAT | O_WRONLY, 0644);
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	}
	else
	{
		pipex->tmp_filename = NULL;
		pipex->infile = open(argv[1], O_RDONLY);
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	}
	if (pipex->infile < 0)
	{
		perror(argv[1]);
		pipex->infile = open("/dev/null", O_RDONLY);
	}
	if (pipex->outfile < 0)
		perror(argv[argc - 1]);
}

int	cdup2(int fd_from, int fd_to)
{
	int	ret_val;

	ret_val = dup2(fd_from, fd_to);
	if (fd_from > -1)
		close(fd_from);
	return (ret_val);
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
		free(buf);
		ft_putstr_fd("here_doc>", 1);
		buf = get_next_line(STDIN_FILENO);
	}
	free(buf);
	free(delimiter_nl);
	close(pipex->infile);
	pipex->infile = open(pipex->tmp_filename, O_RDONLY);
	if (pipex->infile < 0)
		ft_clean_exit(pipex, EXIT_FAILURE);
}

void	start_wait(t_pipex *pipex, pid_t pid, int i, int def_status)
{
	int	status;

	(void)i;
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	if (status == -1)
		ft_clean_exit(pipex, EXIT_FAILURE);
	if (WIFEXITED(status))
		ft_clean_exit(pipex, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_clean_exit(pipex, 128 + WTERMSIG(status));
	ft_clean_exit(pipex, def_status);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	t_bool	here_doc_bool;
	pid_t	pid;
	int		i;

	if (argc < 5)
		return (usage());
	here_doc_bool = (argc > 1 && ft_strncmp(argv[1], "here_doc", 9) == 0);
	set_files(&pipex, argc, argv, here_doc_bool);
	i = 2 + here_doc_bool;
	if ((here_doc_bool && argc < 6) || argc < 5)
		return (usage());
	else if (here_doc_bool)
		here_doc(&pipex, argv[2]);
	cdup2(pipex.infile, STDIN_FILENO);
	while (i < argc - 2)
		create_linked_child(&pipex, argv[i++], env, 0);
	if (cdup2(pipex.outfile, STDOUT_FILENO) == -1)
		start_wait(&pipex, 0, i, 1);
	close(pipex.outfile);
	pid = create_linked_child(&pipex, argv[argc - 2], env, 1);
	close(0);
	start_wait(&pipex, pid, ++i - here_doc_bool, 0);
	return (0);
}
