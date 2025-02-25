/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:47:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/02/25 17:56:33 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

int	create_linked_child(int input_fd, int output_fd, char *line, char *env[])
{
	char	**cmd;

	if (input_fd < 0 || output_fd < 0)
		return (2);
	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	close(input_fd);
	cmd = ft_split(line, ' ');
	try_exec(cmd, env);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[], char *env[])
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;
	int	file1_fd;
	int	file2_fd;

	if (argc < 5)
	{
		ft_printf("usage : ./pipex <file1> <cmd1> <cmd2> <file2>\n");
		return (-1);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("");
		return (1);
	}
	file1_fd = open(argv[1], O_RDONLY);
	if (file1_fd < 0)
		perror(argv[1]);
	file2_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2_fd < 0)
		perror(argv[4]);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		create_linked_child(file1_fd, pipe_fd[1], argv[2], env);
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		close(pipe_fd[1]);
		create_linked_child(pipe_fd[0], file2_fd, argv[3], env);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid2, NULL, 0);
	waitpid(pid1, NULL, 0);
	return (0);
}
