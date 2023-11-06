#include <unistd.h>

void	run_cmd(char	*cmd)
{
	char	*file = "/bin/bash";
	char	*const args[] = {file, "-c", cmd, NULL};
	char	*const env[] =  {NULL};
	execve(file, args, env);
}

int	main(int argc, char **argv)
{
	run_cmd(argv[1]);
}
