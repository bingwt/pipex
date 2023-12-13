/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:00:24 by btan              #+#    #+#             */
/*   Updated: 2023/12/14 01:47:08 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	run_cmd(char *args)
{
	char	**cmd;
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
	wait(NULL);
	while (*cmd)
		free(*(cmd++));
	free(cmd);
	free(program);
	ft_printf("parent");
}

static void	pipex(char *infile, char *in_cmd, char *out_cmd, char *outfile)
{
	int	p_fd[2];
	int	in_fd;
	int	out_fd;


	in_fd = open(infile, O_RDONLY);
	out_fd = open(outfile, O_WRONLY | O_CREAT, 0644);
	dup2(0, in_fd);
	run_cmd(in_cmd);
}

int	main(int argc, char **argv)
{
	int	og_stdin;

	og_stdin = dup(0);
	close(0);
	pipex(argv[1], argv[2], argv[3], argv[4]);
}
