/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 01:22:16 by btan              #+#    #+#             */
/*   Updated: 2024/01/02 02:28:16 by btan             ###   ########.fr       */
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
	char	**env;
	char	**temp;
	int		i;
	char	*path;
	char	*program;

	env = NULL;
	i = 0;
	while (!env)
	{
		env = ft_split(envp[i++], '=');
		if (ft_strncmp(*env, "PATH", 4))
		{
			free_strs(env);
			env = NULL;
		}
	}
	temp = ft_split(env[1], ':');
	free_strs(env);
	env = temp;
	while (*temp)
	{
		program = ft_strjoin(*(temp++), cmd);
		if (!access(program, X_OK))
			break ;
		free(program);
	}
	path = ft_strdup(program);
	free_strs(env);
	free(program);
	return path;
}
