/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:00:24 by btan              #+#    #+#             */
/*   Updated: 2024/01/02 16:11:29 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	run_cmd(char *args, char **envp)
{
	char	**cmd;
	char	*program;
	char	*path;

	if (!args)
		return ;
	cmd = ft_split(args, ' ');
	program = ft_strjoin("/", cmd[0]);
	path = get_path(envp, program);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		free_strs(cmd);
		if (path)
			free(path);
		free(program);
		exit(127);
	}
	execve(path, cmd, NULL);
}

static void	rd_cmd(int fd, int *p_fd, int dir)
{
	dup2(fd, !dir);
	close(fd);
	dup2(p_fd[dir], dir);
	close(p_fd[0]);
	close(p_fd[1]);
}

static void	child(t_pipe params, char *cmd, int dir, char **envp)
{
	int	fd;

	if (dir == 1)
		fd = open(params.args[1], O_RDONLY);
	else
		fd = open(params.args[4], O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		exit(1);
	rd_cmd(fd, params.pipe, dir);
	run_cmd(cmd, envp);
	close(fd);
	exit(0);
}

void	pipex(char **args, char **envp)
{
	int		p_fd[2];
	int		pid;
	t_pipe	params;

	params.args = args;
	pipe(p_fd);
	params.pipe = p_fd;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child(params, args[2], 1, envp);
	waitpid(pid, NULL, 0);
	close(p_fd[1]);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child(params, args[3], 0, envp);
	waitpid(pid, NULL, 0);
	exit(0);
}
