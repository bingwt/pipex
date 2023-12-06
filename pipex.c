/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:27:40 by btan              #+#    #+#             */
/*   Updated: 2023/12/07 02:01:17 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pipex.h>

static void	run_cmd(char **args)
{
	char	*program;

	if (!args)
		return ;
	program = ft_strjoin("/bin/", args[0]);
	if (execve(program, args, NULL) == -1)
	{
		perror(NULL);
		exit(0);
	}
		//ft_printf("%s: command not found\n", args[0]);
}

static void	pipex(int fd, char ***cmd)
{
	int	pid;

	dup2(fd, 0);
	pid = fork();
	if (pid == 0)
		run_cmd(*cmd);
	close(fd);
}

int	main(int argc, char **argv)
{
	int		origin;
	int		fd;
	char	**cmd;
	char	**temp;

	origin = dup(0);
	fd = open(argv[1], O_RDONLY);
	cmd = ft_split(argv[2], ' ');
	pipex(fd, &cmd);
	temp = cmd;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(cmd);
	dup2(origin, 0);
	close(origin);
	return (0);
}
