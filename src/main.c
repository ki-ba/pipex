/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:47:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 18:04:48 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_multifree(int n_simple, int n_arr, ...)
{
	int		i;
	va_list	args;
	char	*current_var;
	char	**current_array;

	i = 0;
	while (i < n_simple)
	{
		current_var = va_arg(args, char *);
		free(current_var);
	}
	while (i < n_arr - n_simple)
	{
		current_array = va_arg(args, char **);
		free_arr(current_array);
	}
}

void	create_linked_child(char *line, char *env[], int last)
{
	char	**cmd;
	int		child_pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	child_pid = fork();
	if (child_pid < 0)
		exit(EXIT_FAILURE);
	if (child_pid == 0)
	{
		cmd = ft_split(line, ' ');
		close(pipe_fd[0]);
		if (!last)
			dup2(pipe_fd[1], STDOUT_FILENO);
		try_exec(cmd, env);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(child_pid, NULL, 0);
	}
}

int	str_is_alnum(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}

char	*create_random_str(void)
{
	int		urandom;
	char	*random_str;

	random_str = malloc((TMP_FILENAME_LENGTH + 1) * sizeof(char));
	random_str[0] = '\0';
	urandom = open("/dev/urandom", O_RDONLY);
	while (!random_str[0] || !str_is_alnum(random_str)
		|| ft_strlen(random_str) != 8)
		read(urandom, random_str, 8);
	return (concat(2, "tmp_", random_str));
}

int	set_files(t_pipex *pipex, int argc, char *argv[], int here_doc)
{
	char	*random_filename;

	if (here_doc)
	{
		random_filename = create_random_str();
		pipex->infile = open(random_filename, O_CREAT | O_WRONLY, 0644);
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
		free(random_filename);
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

void	setup_pipex(t_pipex *pipex, int infile, int outfile, char *argv[])
{
	pipex->infile = infile;
	pipex->outfile = outfile;
	pipex->cmd = duplicate_arr(argv);
	pipex->args = duplicate_arr(argv);
	pipex->cmd_count = get_arr_size(argv);
}

int	usage(void)
{
	return (ft_printf("usage : ./pipex <[here_doc LIMITER] | infile> <cmd1> <cmd2> <outfile>\n"));
}
void	free_pipex(t_pipex *pipex)
{
	free_arr(pipex->cmd);
	free_arr(pipex->args);
}

void	here_doc(t_pipex *pipex, char *delimiter)
{
	char	*buf;

	ft_putstr_fd("here_doc>", 1);
	buf = get_next_line(STDIN_FILENO);
	while (buf && ft_strncmp(buf, delimiter, ft_strlen(delimiter) + 1))
	{
		write(pipex->infile, buf, ft_strlen(buf));
		write(pipex->infile, "\n", 1);
		ft_putstr_fd("here_doc>", 1);
		buf = get_next_line(STDIN_FILENO);
	}
	(void)pipex;
}
int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	int		here_doc_bool;
	int		i;

	here_doc_bool = ft_strncmp(argv[1], "here_doc", 9) == 0;
	i = 2 + here_doc_bool;
	if (here_doc_bool)
	{
		if (argc < 6)
			return (usage());
		here_doc(&pipex, argv[2]);
	}
	else if (argc < 5)
		return (usage());
	set_files(&pipex, argc, argv, (ft_strncmp(argv[1], "here_doc", 9) == 0));
	dup2(pipex.outfile, STDIN_FILENO);
	while (i < argc - 2)
		create_linked_child(argv[i++], env, 0);
	dup2(pipex.outfile, STDOUT_FILENO);
	create_linked_child(argv[argc - 2], env, 1);
	return (0);
}
