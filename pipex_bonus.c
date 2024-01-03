/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:00:24 by btan              #+#    #+#             */
/*   Updated: 2024/01/03 01:53:24 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static void	run_cmd(char *args, char **envp)
{
	char	**cmd;
	char	*program;
	char	*path;

	if (!args)
		return ;
	cmd = ft_split(args, ' ');
	if (!access(args, X_OK))
			execve(args, cmd, envp);
	program = ft_strjoin("/", cmd[0]);
	path = get_path(envp, program);
	if (!path)
	{
		handle_error(cmd[0], "CMD_NOT_FOUND");
		free_strs(cmd);
		if (path)
			free(path);
		free(program);
		exit(127);
	}
	execve(path, cmd, envp);
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
	{
		if (access(params.args[1], F_OK))
			handle_error(params.args[1], "NO_FILE");
		fd = open(params.args[1], O_RDONLY);
		if (fd == -1)
			handle_error(params.args[1], "NO_PERMS");
	}
	else
	{
		fd = open(params.args[4], O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			handle_error(params.args[4], "NO_PERMS");
	}
	rd_cmd(fd, params.pipe, dir);
	run_cmd(cmd, envp);
	close(fd);
	exit(0);
}

static void	multi_pipe(char *cmd, char **envp)
{
	int	p_fd[2];
	int	pid;

	pipe(p_fd);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		rd_cmd(0, p_fd, 1);
		run_cmd(cmd, envp);
	}
	rd_cmd(1, p_fd, 0);
	run_cmd(cmd, envp);
}

void	pipex(int argc, char **args, char **envp)
{
	int		p_fd[2];
	int		pid;
	t_pipe	params;
	int		i;

	params.args = args;
	pipe(p_fd);
	params.pipe = p_fd;
	i = 2;
	open(params.args[argc - 1], O_WRONLY | O_CREAT, 0644);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child(params, args[2], 1, envp);
	waitpid(pid, NULL, 0);
	close(p_fd[1]);
	while (++i != (argc - 1))
		multi_pipe(args[i], envp);
	child(params, args[3], 0, envp);
}