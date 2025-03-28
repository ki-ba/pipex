/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:39:17 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/10 15:22:19 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "fcntl.h"
# include "libft.h"
# include <sys/wait.h>

/* ### DATA STRUCTURES ### */

typedef struct s_pipex
{
	pid_t	infile;
	pid_t	outfile;

}			t_pipex;

/* ### PROTOTYPES ### */

/* parsing.c */

char		*basename(char str[]);

/* execution.c */

char		**extract_path(char *env[]);
char		*find_path(char *command, char **path);
int			try_exec(char **cmd, char *env[]);
pid_t		create_linked_child(t_pipex *pipex, char *line, char *env[],
				int last);

/* error.c */

int			usage(void);
int			ft_clean_exit(t_pipex *pipex, int exit_status);
int			sclose(int fd);
#endif
