/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:47:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/02/19 16:46:18 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

int	main(int argc, char *argv[], char *env[])
{
	int		pipe_fd[2];
	int		pid1;
	int		pid2;
	int		file1_fd;
	int		file2_fd;
	char	*errfile;
	char	**cmd1;
	char	**cmd2;

	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');

	if (argc < 5)
	{
		ft_printf("usage : ./pipex <file1> <cmd1> <cmd2> <file2>\n");
		return (-1);
	}
	file1_fd = open(argv[1], O_RDONLY);
	file2_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file1_fd < 0 || file2_fd < 0) // handle file opening errors
	{
		errfile = "";
		if (file1_fd < 0)
			errfile = argv[1];
		else if (file2_fd < 0)
			errfile = argv[4];
		perror(argv[1]);
		return (40);
	}
	if (pipe(pipe_fd) == -1)
	{
		ft_printf("could not create pipe\n");
		return (1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		return (2); // Couldnt fork
	}

	if (pid1 == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO); // write to right side of pipe
		dup2(file1_fd, STDIN_FILENO);
		try_exec(cmd1, env);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}

/* 	pid2 = fork();
	if (pid2 < 0)
	{
		free_arr(path);
		ft_printf("2nd fork failed\n");
		return (2); // Couldnt fork
	}
	if (pid2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO); // read from right side of pipe
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		dup2(file2_fd, STDOUT_FILENO); // write to fd2;
		try_exec(cmd2, env);
	} */


	free_arr(cmd1);
	free_arr(cmd2);

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
