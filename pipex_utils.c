/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 01:22:16 by btan              #+#    #+#             */
/*   Updated: 2024/01/02 01:34:54 by btan             ###   ########.fr       */
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

char	*get_path(char **envp)
{
	char	**env;
	char	**temp;
	int		i;
	char	*path;

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
		if (!access(*(temp++), X_OK))
			break ;
	path = ft_strdup(*(--temp));
	free_strs(env);
	return path;
}
