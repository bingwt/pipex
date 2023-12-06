/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:27:40 by btan              #+#    #+#             */
/*   Updated: 2023/12/07 03:20:04 by btan             ###   ########.fr       */
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

static void	pipex(int fd, int *pipe_fds, char ***cmd, int inout)
{
	int	origin;
	int	pid;
	
	origin = dup(inout);
	if (inout)
	{
		dup2(pipe_fds[0], 0);
		dup2(fd, 1);
	}
	else
	{
		dup2(pipe_fds[1], 1);
		dup2(fd, 0);
	}
	pid = fork();
	if (pid == 0)
		run_cmd(*cmd);
	close(fd);
	dup2(origin, inout);
	close(origin);
}

int	main(int argc, char **argv)
{
	int		origin;
	int		fd_in;
	int		fd_out;
	char	**cmd;
	int	pipe_fds[2];

	pipe(pipe_fds);
	origin = dup(0);
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[4], O_WRONLY | O_CREAT, 0644);
	cmd = ft_split(argv[2], ' ');
	pipex(fd_in, pipe_fds, &cmd, 0);
	cmd = ft_split(argv[3], ' ');
	pipex(fd_out, pipe_fds, &cmd, 1);
	close(origin);
	return (0);
}
