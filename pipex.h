/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:39:17 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/08 18:44:17 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "fcntl.h"
# include "libft.h"
# include <sys/wait.h>

# ifndef TMP_FILENAME_LENGTH
#  define TMP_FILENAME_LENGTH 1
# endif

typedef enum bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_pipex
{
	pid_t	infile;
	pid_t	outfile;

	char	*tmp_filename;
}			t_pipex;

/* parsing.c */
int				ft_is_non_empty(char str[]);
char			*basename(char str[]);

/* execution.c */

char			**extract_path(char *env[]);
char			*find_path(char *command, char **path);
int				try_exec(char **cmd, char *env[]);
void			create_linked_child(t_pipex *pipex, char *line, char *env[], int last);

/* arr_utils.c */

void			free_arr(char **arr);
void			print_arr(char **arr);
void			str_arr_suffix(char **arr, char *suffix);
char			**duplicate_arr(char **arr);
int				get_arr_size(char **arr);

/* str_utils.c */

void			heap_add_suffix(const char *suffix, char **s1);
void			heap_add_prefix(const char *prefix, char *s2);
char			*concat(size_t n, ...);
t_bool			str_is_alnum(char *str);
char			*create_random_str(void);

/* error.c */

int				usage(void);
void			ft_clean_exit(t_pipex *pipex, int exit_status);
void			ft_multifree(int n_simple, int n_arr, ...);
#endif
