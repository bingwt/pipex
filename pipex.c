/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:27:40 by btan              #+#    #+#             */
/*   Updated: 2023/11/28 16:37:12 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pipex.h>

static void	run_cmd(char **args)
{
	char	*program;

	if (!args)
		return ;
	program = ft_strjoin("/bin/", args[0]);
	if (execve(program, args, NULL) == -1)
	{
		perror(NULL);
		exit(0);
	}
		//ft_printf("%s: command not found\n", args[0]);
}

static char	**cmd_rd(char *file, char *cmd)
{
	char	*program;
	char	*temp;
	char	**args;

	if (!file || !cmd)
		return (NULL);
	program = ft_strjoin(cmd, " ");
	temp = ft_strjoin(program, file);
	args = ft_split(temp, ' ');
	free(program);
	free(temp);
	return (args);
}

//static void	out_rd()
//{
//	int	fd;
//
//	fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
//	dup2(fd, 1);
//	close(fd);
//	ft_printf("This is a test");
//}

static void	pipex(char	***args)
{
	int	id;
	int	i;
	
	id = fork();
	if (id == 0)
		run_cmd(*args);
	else
		wait(0);
	i = 0;
	while (args[0][i])
		free(args[0][i++]);
	free(args[0]);
	ft_printf("Done!");
}	

int	main(int argc, char **argv)
{
	char	**args;

	args = cmd_rd(argv[1], argv[2]);
	pipex(&args);
	return (0);
}
