/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:39:17 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/04 14:16:49 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "fcntl.h"
# include "libft.h"

typedef struct s_fdlist
{
	struct s_fdlist	*next;
	int				fd;
}					t_fdlist;

// ERROR

void				ft_clean_exit(int errno);

// PARSING
int					ft_is_non_empty(char str[]);
char				*basename(char str[]);

// EXECUTION

char				**extract_path(char *env[]);
char				*find_path(char *command, char **path);
int					try_exec(char **cmd, char *env[]);

// ARR_UTILS

void				free_arr(char **arr);
void				print_arr(char **arr);
void				str_arr_suffix(char **arr, char *suffix);
char				**duplicate_arr(char **arr);

// STR_UTILS

void				heap_add_suffix(const char *suffix, char **s1);
void				heap_add_prefix(const char *prefix, char *s2);
char				*concat(size_t n, ...);

#endif
