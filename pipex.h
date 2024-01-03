/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 02:55:12 by btan              #+#    #+#             */
/*   Updated: 2024/01/03 17:04:44 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <libft.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_pipe_parameters
{
	char	**args;
	int		*pipe;
	int		*files;
}	t_pipe;

void	free_strs(char **strs);
char	*get_path(char **envp, char *cmd);
int		handle_error(char *vars, char *error);
void	pipex(char **args, char **envp);
#endif
