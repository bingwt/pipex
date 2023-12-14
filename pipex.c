/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:00:24 by btan              #+#    #+#             */
/*   Updated: 2023/12/15 02:38:46 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	run_cmd(char *args)
{
	char	**cmd;
	char	**ptr;
	char	*program;
	int		pid;

	if (!args)
		return ;
	cmd = ft_split(args, ' ');
	program = ft_strjoin("/bin/", cmd[0]);
	pid = fork();
		if (pid == 0 && execve(program, cmd, NULL) == -1)
		{
			ft_printf("%s: command not found\n", cmd[0]);
			exit(0);
		}
	ptr = cmd;
	while (*cmd)
		free(*(cmd++));
	free(ptr);
	free(program);
}

static void	redirect(int fd, int *p_fd, int dir)
{
	if (dir == 0)
		dup2(p_fd[1], 1);
	else if (dir == 1)
		dup2(p_fd[0], 0);
	dup2(fd, dir);
	close(fd);
	close(p_fd[0]);
	close(p_fd[1]);
}

int	main(int argc, char **argv)
{
	int	p_fd[2];
	int	pid1;
	int	pid2;
	int	infile;
	int	outfile;

	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_WRONLY | O_CREAT, 0644);
	pipe(p_fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(infile, 0);
		close(infile);
		dup2(p_fd[1], 1);
		close(p_fd[0]);
		close(p_fd[1]);
		run_cmd(argv[2]);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		close(p_fd[1]);
		dup2(outfile, 1);
		close(outfile);
		run_cmd(argv[3]);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
