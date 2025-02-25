/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:15:01 by kbarru            #+#    #+#             */
/*   Updated: 2025/02/25 17:56:27 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 *	@brief extracts the PATH formatted to an array of strings.
 *	@param env the environment variable.
 *	@returns the PATH as an array of strings.
 */
char	**extract_path(char *env[])
{
	size_t	i;
	size_t	offset;
	char	*path_line;
	char	**path;

	offset = ft_strlen("PATH=");
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", offset))
		++i;
	path_line = ft_substr(env[i], offset, ft_strlen(env[i]) - offset);
	path = ft_split(path_line, ':');
	free(path_line);
	return (path);
}

/*
 *	@brief finds a working path to the binary name passed as parameter.
 *	@param command the binary name to look for.
 *	@param path the PATH variable split as an array of strings.
 *	@returns the first correct path found.
 *	@note if `command` is a relative or absolute path, no searching
 *	outside of specified path is done.
 */
char	*find_path(char *command, char **path)
{
	int		access_rval;
	char	*current_path;
	char	*c_basename;
	size_t	i;

	if (!command || !path)
		return (NULL);
	c_basename = basename(command);
	access_rval = 1;
	i = 0;
	while (path[i] && access_rval != 0)
	{
		current_path = concat(3, path[i], "/", c_basename);
		access_rval = access(current_path, F_OK & X_OK);
		if (access_rval != 0)
			free(current_path);
		++i;
	}
	free(c_basename);
	free(command);
	if (access_rval != 0)
		return (NULL);
	return (current_path);
}

int	try_exec(char **cmd, char *env[])
{
	char	**path;
	char	*cmd_tried;
	char	*c_basename;

	c_basename = basename(cmd[0]);
	if (ft_strncmp(c_basename, cmd[0], ft_strlen(c_basename)) != 0)
	{
		execve(cmd[0], cmd, env);
		free(c_basename);
	}
	else
	{
		free(c_basename);
		cmd_tried = ft_strdup(cmd[0]);
		path = extract_path(env);
		cmd[0] = find_path(cmd[0], path);
		free_arr(path);
		if (cmd && cmd[0])
			execve(cmd[0], cmd, env);
		perror(cmd_tried);
		free(cmd_tried);
		free_arr(cmd);
	}
	return (1);
}
