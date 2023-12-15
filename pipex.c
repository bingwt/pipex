/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:00:24 by btan              #+#    #+#             */
/*   Updated: 2023/12/15 18:40:50 by btan             ###   ########.fr       */
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
	ptr = cmd;
	while (*cmd)
		free(*(cmd++));
	free(ptr);
	free(program);
}

static void	rd_cmd(char *file, int *p_fd, int dir)
{
	int	fd;

	if (dir == 1)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
			perror(NULL);
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

	pipe(p_fd);
	pid = fork();
	if (pid == -1)
			perror(NULL);
	if (pid == 0)
	{
		rd_cmd(infile, p_fd, 1);
		run_cmd(cmd1);
	}
	waitpid(pid, NULL, 0);
	rd_cmd(outfile, p_fd, 0);
	run_cmd(cmd2);
	//ft_printf("%s\n", outfile);
	//ft_printf("%s\n", cmd2);
	exit(127);
}
