/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:00:24 by btan              #+#    #+#             */
/*   Updated: 2023/12/14 03:36:31 by btan             ###   ########.fr       */
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

static void	rd_cmd(int fd, char *cmd, int *p_fd, int in_out)
{
	dup2(fd, !in_out); 
	close(fd);
	dup2(p_fd[in_out], in_out);
	close(p_fd[in_out]);
	run_cmd(cmd);
}

static void	pipex(char *infile, char *in_cmd, char *out_cmd, char *outfile)
{
	int	p_fd[2];
	int	in_fd;
	int	out_fd;
	int	pid;
	char	*line;
	int original_stdout;

	original_stdout = dup(1);
	pipe(p_fd);
	in_fd = open(infile, O_RDONLY);
	out_fd = open(outfile, O_WRONLY | O_CREAT, 0644);
	dup2(in_fd, 0);
	close(in_fd);
  	dup2(p_fd[WRITE_END], 1);
	pid = fork();
	if (pid == 0)
	{
		run_cmd(in_cmd);
	}
	else
	{
		dup2(p_fd[WRITE_END], 1);
		close(p_fd[WRITE_END]);
		run_cmd(out_cmd);
		dup2(out_fd, 1);
		close(out_fd);
		wait(NULL);
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

int	main(int argc, char **argv)
{
	int	og_stdin;

	og_stdin = dup(0);
	close(0);
	pipex(argv[1], argv[2], argv[3], argv[4]);
}
