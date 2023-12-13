/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:00:24 by btan              #+#    #+#             */
/*   Updated: 2023/12/14 04:17:42 by btan             ###   ########.fr       */
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

static void	redirect(int in_fd, int out_fd)
{
	dup2(in_fd, 0);
	close(in_fd);
	dup2(out_fd, 1);
	close(out_fd);
}

static void	rd_cmd(char *file, char *cmd, int p_end, int dir)
{
	int	fd;

	if (!dir)
	{
		fd = open(file, O_RDONLY);
		redirect(fd, p_end);
		run_cmd(cmd);
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT, 0644);
		redirect(p_end, fd);
		run_cmd(cmd);
	}
}

int	main(int argc, char **argv)
{
	int	p_fd[2];
	int	pid;
	char	*line;

	pipe(p_fd);
	pid = fork();
	if (pid == 0)
		rd_cmd(argv[1], argv[2], p_fd[WRITE_END], 0);
	else
	{
		wait(NULL);
		rd_cmd(argv[4], argv[3], p_fd[READ_END], 1);
		line = get_next_line(p_fd[READ_END]);
		while (line != NULL)
		{
			ft_printf("%s", line);
			free(line);
			line = get_next_line(p_fd[READ_END]);
		}
		exit(1);
	}
}
