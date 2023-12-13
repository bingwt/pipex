/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:00:24 by btan              #+#    #+#             */
/*   Updated: 2023/12/14 03:01:50 by btan             ###   ########.fr       */
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
	wait(NULL);
	ptr = cmd;
	while (*cmd)
		free(*(cmd++));
	free(ptr);
	free(program);
	ft_printf("parent");
}

static void	pipex(char *infile, char *in_cmd, char *out_cmd, char *outfile)
{
}
int	main(int argc, char **argv)
{
	int	og_stdin;

	og_stdin = dup(0);
	close(0);
	pipex(argv[1], argv[2], argv[3], argv[4]);
}
