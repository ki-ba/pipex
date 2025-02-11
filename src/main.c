/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:47:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/02/11 16:45:40 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int		fd[2];
	int		pid1;
	int		pid2;

	int		fd1;
	int		fd2;
	char	*errfile;


	(void)argv;
	(void)argc;

	if (argc < 5)
	{
		ft_printf("usage : ./pipex <file1> <cmd1> <cmd2> <file2>\n");
		return (-1);
	}

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_RDWR);


	if (fd1 < 0 || fd2 < 0)
	{
		errfile = "";
		if (fd1 < 0)
			errfile = argv[1];
		else if (fd2 < 0)
			errfile = argv[4];
		ft_printf("could not open file %s\n", errfile);
		return (40);
	}

	char *arg[] = {"/bin/cat", argv[1], NULL};
	char *env[] = {"PATH=/home/kbarru/bin:/home/kbarru/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/kbarru/.dotnet/tools:/home/kbarru/.config/Code/User/globalStorage/github.copilot-chat/debugCommand", NULL};

	if (pipe(fd) == -1)
		return 1;

	pid1 = fork();

	if (pid1 < 0)
		return (2); // Couldnt fork

	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO); // write to right side of pipe
		close(fd[0]);
		close(fd[1]);
		execve("/bin/rev", arg, env);
	}

	pid2 = fork();

	if (pid2 < 0)
		return (1);

	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO); // read from left side of pipe
		close(fd[0]);
		dup2(fd2, STDOUT_FILENO); // write to fd2;
		close(fd[1]);
		execve("/bin/cat", arg, env);
	}

	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
		return (0);
}
