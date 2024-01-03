/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:00:24 by btan              #+#    #+#             */
/*   Updated: 2024/01/03 16:42:40 by btan             ###   ########.fr       */
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
	if (dir == 1)
	{
		if (access(params.args[1], F_OK))
			handle_error(params.args[1], "NO_FILE");
		if (params.files[0] == -1)
			handle_error(params.args[1], "NO_PERMS");
	}
	else
		if (params.files[1] == -1)
			handle_error(params.args[4], "NO_PERMS");
	rd_cmd(params.files[!dir], params.pipe, dir);
	run_cmd(cmd, envp);
	close(params.files[!dir]);
	exit(0);
}

void	pipex(char **args, char **envp)
{
	int		p_fd[2];
	int		pid;
	t_pipe	params;
	int		files[2];

	params.args = args;
	pipe(p_fd);
	params.pipe = p_fd;
	files[0] = open(params.args[1], O_RDONLY);
	files[1] = open(params.args[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	params.files = files;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child(params, args[2], 1, envp);
	waitpid(pid, NULL, WNOHANG);
	close(p_fd[1]);
	child(params, args[3], 0, envp);
}
