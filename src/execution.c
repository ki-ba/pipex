/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:15:01 by kbarru            #+#    #+#             */
/*   Updated: 2025/02/19 16:39:04 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
*	@brief extracts the PATH formatted to an array of strings.
*	@param the environment variable.
*	@returns the PATH as an array of strings.
*/
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

/*
*	@brief finds a working path to the binary name passed as parameter.
*	@param command the binary name to look for.
*	@param path the PATH variable split.
*	@returns the first correct path found.
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
	i = 0;
	access_rval = access(command, F_OK & X_OK);
	while(path[i] && access_rval != 0)
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
	char **path;

	path = extract_path(env);
	cmd[0] = find_path(cmd[0], path);
	free_arr(path);
	if (cmd && cmd[0])
		execve(cmd[0], cmd, env);
	free_arr(cmd);
	exit(EXIT_FAILURE);
}
