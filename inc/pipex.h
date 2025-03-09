/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:39:17 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 11:12:40 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "fcntl.h"
# include "libft.h"
# include <sys/wait.h>

/* ### MACROS ### */

# ifndef BONUS
#  define BONUS FALSE
# endif

/* ### DATA STRUCTURES ### */

# if (BONUS >= TRUE)
typedef struct s_pipex
{
	pid_t	infile;
	pid_t	outfile;

	char	*tmp_filename;
}			t_pipex;

# else
typedef struct s_pipex
{
	pid_t	infile;
	pid_t	outfile;

}			t_pipex;
# endif


/* ### PROTOTYPES ### */

/* parsing.c */
char			*basename(char str[]);

/* execution.c */

char			**extract_path(char *env[]);
char			*find_path(char *command, char **path);
int				try_exec(char **cmd, char *env[]);
void			create_linked_child(t_pipex *pipex, char *line, char *env[], int last);

/* arr_utils.c */

void			str_arr_suffix(char **arr, char *suffix);
char			**duplicate_arr(char **arr);
int				get_arr_length(char **arr);

/* str_utils.c */

void			heap_add_suffix(const char *suffix, char **s1);
void			heap_add_prefix(const char *prefix, char *s2);
char			*concat(size_t n, ...);
char			*create_random_str(void);

/* error.c */

int				usage(void);
void			ft_clean_exit(t_pipex *pipex, int exit_status);
void			ft_multifree(int n_simple, int n_arr, ...);

#endif
