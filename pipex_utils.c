/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 01:22:16 by btan              #+#    #+#             */
/*   Updated: 2024/01/02 16:12:25 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	free_strs(char **strs)
{
	char	**temp;

	temp = strs;
	while (*strs)
		free(*(strs++));
	free(temp);
}

char	*get_path(char **envp, char *cmd)
{
	char	*program_path;
	char	**path;
	char	**ptr;
	char	*program;

	while (*envp)
		if (!ft_strncmp(*(envp++), "PATH=", 5))
			break ;
	path = ft_split(*(--envp) + 5, ':');
	ptr = path;
	program = ft_strjoin("/", cmd);
	while (*ptr)
	{
		program_path = ft_strjoin(*(ptr++), program);
		if (!access(program_path, X_OK))
			break ;
		free(program_path);
		program_path = NULL;
	}
	free(program);
	free_strs(path);
	return (program_path);
}
