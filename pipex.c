/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:27:40 by btan              #+#    #+#             */
/*   Updated: 2023/11/27 11:20:19 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pipex.h>

static void	run_cmd(char *cmd)
{
	char	**args;
	char	*program; 

	if (!cmd)
		return ;
	args = ft_split(cmd, ' ');
	program = ft_strjoin("/bin/", args[0]);
	if (execve(program, args, NULL) == -1)
		ft_printf("%s: command not found\n", args[0]);
	while (!*args)
		free(*(args++));
	free(args);
	free(program);
}

int	main(int argc, char **argv)
{
	run_cmd(argv[1]);
}