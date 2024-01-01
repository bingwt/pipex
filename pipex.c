/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:00:24 by btan              #+#    #+#             */
/*   Updated: 2024/01/02 01:30:56 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	run_cmd(char *args, char **envp)
{
	char	**cmd;
	char	*program;
	int		pid;
	char	*path;

	if (!args)
		return ;
	cmd = ft_split(args, ' ');
	path = ft_strjoin(get_path(envp), "/");
	program = ft_strjoin(path, cmd[0]);
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
	free_strs(cmd);
	free(program);
	free(path);
}

static void	rd_cmd(int fd, int *p_fd, int dir)
{
	dup2(fd, !dir);
	close(fd);
	dup2(p_fd[dir], dir);
	close(p_fd[0]);
	close(p_fd[1]);
}

static void	child(char *file, char *cmd, int *p_fd, int dir, char **envp)
{
	int	fd;

	if (dir == 1)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_CREAT, 0644);	
	if (fd == -1)
		exit(1);	
	rd_cmd(fd, p_fd, dir);
	run_cmd(cmd, envp);
	close(fd);
	exit(0);
}

void	pipex(char *infile, char *cmd1, char *cmd2, char *outfile, char **envp)
{
	int	p_fd[2];
	int	pid;
	pipe(p_fd);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child(infile, cmd1, p_fd, 1, envp);
	waitpid(pid, NULL, 0);
	close(p_fd[1]);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child(outfile, cmd2, p_fd, 0, envp);
	waitpid(pid, NULL, 0);
	exit(0);
}
