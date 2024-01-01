//execve
//#include <unistd.h>
//#include <libft.h>
//
//void	run_cmd(char *cmd)
//{
//	char	**args;
//	char	*program; 
//
//	args = ft_split(cmd, ' ');
//	program = ft_strjoin("/bin/", args[0]);
//	if (execve(program, args, NULL) == -1)
//		ft_printf("%s: command not found\n", args[0]);
//}
//
//int	main(int argc, char **argv)
//{
//	run_cmd(argv[1]);
//}

//dup2(2)
//#include <fcntl.h>
//#include <unistd.h>
//#include <libft.h>
//
//int	main()
//{
//
//	int	fd;
//	int	original_stdout;
//
//	fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
//	original_stdout = dup(1);
//	dup2(fd, 1);
//	close(fd);
//	ft_printf("This is a test");
//	dup2(original_stdout, 1);
//	close(original_stdout);
//	ft_putstr_fd("example.txt created\n", 1);
//}

//pipe()
//#include <fcntl.h>
//#include <libft.h>
//#include <pipex.h>
//
//int	main()
//{
//	int	p_fd[2];
//	char	*line;
//
//	pipe(p_fd);
//	dup2(1, p_fd[WRITE_END]);
//	ft_putstr_fd("This is a test\n", 1);
//	ft_putstr_fd("This another is a test\n", 1);
//	line = get_next_line(p_fd[READ_END]);
//	while (line != NULL)
//	{
//		ft_printf("%s", line);
//	}
//	exit(1);
//}

//pipex()
//#include <fcntl.h>
//#include <libft.h>
//#include <pipex.h>
//
//int	main()
//{
//	int	p_fd[2];
//	int	fd;
//	int	pid;
//	char	*line;
//	char	**args;
//
//	args = ft_split(ft_strdup("cat -e"), ' ');
//	pipe(p_fd);
//	fd = open("Makefile", O_RDONLY);
//	dup2(fd, 0);
//	close(fd);
//  	dup2(1, p_fd[WRITE_END]);
//	pid = fork();
//	if (pid == 0)
//	{
//		execve("/bin/cat", args, NULL);
//	}
//	else
//	{
//		close(p_fd[READ_END]);
//		line = get_next_line(p_fd[READ_END]);
//		while (line != NULL)
//			//ft_printf("%s", line);
//		exit(1);
//	}
//}

//access()
#include <fcntl.h>
#include <libft.h>
int	main()
{
	ft_printf("%d\n", access("/home/btan/.local/bin/cat", X_OK));
	ft_printf("%d\n", access("/usr/local/bin/cat", X_OK));
	ft_printf("%d\n", access("/usr/bin/cat", X_OK));
	ft_printf("%d\n", access("/usr/bin/catd", X_OK));
}
