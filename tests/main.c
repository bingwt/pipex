//execve
#include <unistd.h>
#include <libft.h>

void	run_cmd(char *cmd)
{
	char	**args;
	char	*program; 

	args = ft_split(cmd, ' ');
	program = ft_strjoin("/bin/", args[0]);
	if (execve(program, args, NULL) == -1)
		ft_printf("%s: command not found\n", args[0]);
}

int	main(int argc, char **argv)
{
	run_cmd(argv[1]);
}

//dup2(2)
//#include <stdio.h>
//#include <fcntl.h>
//#include <unistd.h>
//
//int	main()
//{
//	int	fd;
//
//	fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
//	dup2(fd, 1);
//	close(fd);
//	printf("This is a test");
//}
