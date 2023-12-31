/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:00:24 by btan              #+#    #+#             */
/*   Updated: 2023/12/19 17:23:54 by btan             ###   ########.fr       */
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
	if (pid == -1)
			perror(NULL);
	if (pid == 0 && execve(program, cmd, NULL) == -1)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		exit(127);
	}
	waitpid(pid, NULL, 0);
	ptr = cmd;
	while (*cmd)
		free(*(cmd++));
	free(ptr);
	free(program);
	exit(0);
}

static void	rd_cmd(int fd, int *p_fd, int dir)
{
	dup2(fd, !dir);
	close(fd);
	dup2(p_fd[dir], dir);
	close(p_fd[0]);
	close(p_fd[1]);
}

void	pipex(char *infile, char *cmd1, char *cmd2, char *outfile)
{
	int	p_fd[2];
	int	pid;
	int	fd;

	pipe(p_fd);
	pid = fork();
	if (pid == -1)
			perror(NULL);
	if (pid == 0)
	{
		fd = open(infile, O_RDONLY);
		if (fd == -1)
			exit(1);
		rd_cmd(fd, p_fd, 1);
		run_cmd(cmd1);
		close(fd);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	pid = fork();
	if (pid == -1)
			perror(NULL);
	if (pid == 0)
	{
		fd = open(outfile, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			exit(1);
		rd_cmd(fd, p_fd, 0);
		run_cmd(cmd2);
		close(fd);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	exit(0);
}
