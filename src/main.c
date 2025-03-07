/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:47:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 09:20:50 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

int	create_linked_child(char *line, char *env[])
{
	char	**cmd;

	cmd = ft_split(line, ' ');
	try_exec(cmd, env);
	exit(EXIT_FAILURE);
}

void	set_files(int *infile, int *outfile, char *file1, char *file2)
{
	*infile = open(file1, O_RDONLY);
	if (*infile < 0)
	{
		perror(file1);
		exit(EXIT_FAILURE);
	}
	*outfile = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile < 0)
	{
		perror(file2);
		exit(EXIT_FAILURE);
	}
}
void	setup_pipex(t_pipex *pipex, int infile, int outfile, char *argv[])
{
	pipex->infile = infile;
	pipex->outfile = outfile;
	pipex->cmd = duplicate_arr(argv);
	pipex->args = duplicate_arr(argv);
	pipex->cmd_count = get_arr_size(argv);
}
int	main(int argc, char *argv[], char *env[])
{
	int	infile;
	int outfile;
	int	pipe_fd[2];
	t_pipex	pipex;
	int	i;

	i = 2;
	if (argc < 5)
		return (ft_printf("usage : ./pipex <file1> <cmd1> <cmd2> <file2>\n"));
	set_files(&infile, &outfile, argv[1], argv[argc - 1]);
	setup_pipex(&pipex, infile, outfile, argv);
	print_arr(pipex.cmd);
	print_arr(pipex.args);
	// dup2(infile, STDIN_FILENO);
	// while (argv[i + 1])
	// {
	// 	if (pipe(pipe_fd) == -1)
	// 	{
	// 		perror("");
	// 		return (1);
	// 	}
	// 	child_pid = fork();
	// 	if (child_pid < 0)
	// 		return (2);
	// 	if (child_pid == 0)
	// 	{
	// 		dup2(pipe_fd[1], STDOUT_FILENO);
	// 		close(pipe_fd[0]);
	// 		close(pipe_fd[1]);
	// 		create_linked_child(argv[i], env);
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	else
	// 	{
	// 		dup2(pipe_fd[0], STDIN_FILENO);
	// 		close(pipe_fd[1]);
	// 		close(pipe_fd[0]);
	// 		waitpid(child_pid, NULL, 0);
	// 		++i;
	// 	}
	// }
	// dup2(outfile, STDOUT_FILENO);
	// create_linked_child(argv[i], env);
	return (0);
}
