/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:47:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/02/12 17:17:09 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

/*
	@brief adds a prefix to a heap string in place.
	@param prefix the prefix to add.
	@param s2 the string to add a prefix to.
*/
void heap_add_prefix(const char *prefix, char *s2)
{
	size_t	prefix_len;
	size_t	s2_len;
	size_t	i;
	char	*s2_dup;

	i = 0;
	s2_dup = ft_strdup(s2);
	prefix_len = ft_strlen(prefix);
	s2_len = ft_strlen(s2);
	free(s2);
	s2 = malloc((prefix_len + s2_len + 1) * sizeof(char));
	if (!s2)
		return ;
	while (i < prefix_len)
	{
		s2[i] = prefix[i];
		++i;
	}
	i = 0;
	while (i < s2_len)
	{
		s2[prefix_len + i] = s2_dup[i];
		++i;
	}
	s2[prefix_len + i] = '\0';
	free(s2_dup);
}

char **extract_path(char *env[])
{
	size_t i;
	size_t offset;
	char *path_line;
	char **path;

	offset = ft_strlen("PATH=");
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", offset))
		++i;

	path_line = ft_substr(env[i], offset, ft_strlen(env[i]) - offset);
	path = ft_split(path_line, ':');
	free(path_line);
	return (path);
}
int try_exec(char **command, char *env[])
{
	char	**path;
	char	*current_command;
	char	**current_args;
	size_t	i;

	i = 0;
	path = extract_path(env);
	execve(command[0], command, env);
	heap_add_prefix("/", command[0]);
	while(path[i])
	{
		current_command = construct_command(path[i], command[0]);

		heap_add_prefix(path[i], current_command);
		ft_printf("%s\n", command[0]);
		execve(command[0], command, env);
		++i;
	}

	return (3);
}
int main(int argc, char *argv[], char *env[])
{
	int		pipe_fd[2];
	int		pid1;
	int		pid2;

	int		file1_fd;
	int		file2_fd;
	char	*errfile;

	char	**exec_str1;
	char	**exec_str2;

	int i = -1;


	if (argc < 5)
	{
		ft_printf("usage : ./pipex <file1> <cmd1> <cmd2> <file2>\n");
		return (-1);
	}

	try_exec(ft_split(argv[2], ' '), env);
	return (0);
	file1_fd = open(argv[1], O_RDONLY);
	file2_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);


	if (file1_fd < 0 || file2_fd < 0) // handle file opening errors
	{
		errfile = "";
		if (file1_fd < 0)
			errfile = argv[1];
		else if (file2_fd < 0)
			errfile = argv[4];
		ft_printf("could not open file %s\n", errfile);
		return (40);
	}

	if (pipe(pipe_fd) == -1)
		return 1;

	pid1 = fork();

	if (pid1 < 0)
		return (2); // Couldnt fork

	if (pid1 == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO); // write to right side of pipe
		dup2(file1_fd, STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve(exec_str1[0], exec_str1, NULL);
		exec_str1[0] = ft_strjoin("/bin/", exec_str1[0]);
		execve(exec_str1[0], exec_str1, NULL);
		exec_str1[0] = ft_strjoin("/usr/", exec_str1[0]);
		execve(exec_str1[0], exec_str1, NULL);
		return (1);
	}

	pid2 = fork();

	if (pid2 < 0)
		return (1);

	if (pid2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO); // read from right side of pipe
		dup2(file2_fd, STDOUT_FILENO); // write to fd2;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve(exec_str2[0], exec_str2, NULL);
		exec_str2[0] = ft_strjoin("/bin/", exec_str2[0]);
		execve(exec_str2[0], exec_str2, NULL);
		exec_str2[0] = ft_strjoin("/usr/", exec_str2[0]);
		execve(exec_str2[0], exec_str2, NULL);
		return (1);
	}

	close(pipe_fd[0]);
	close(pipe_fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
		return (0);
}
