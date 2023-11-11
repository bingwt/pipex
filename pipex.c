/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:27:40 by btan              #+#    #+#             */
/*   Updated: 2023/11/10 12:42:33 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.a"
#include <unistd.h>

char	*rd_left(int fd, char *content)
{
	int	read_bytes;

	read_bytes = 1;
	while (read_bytes)
		read_bytes = read(fd, temp, 1024);
}
char	*rd_right(char *file);
void	run_cmd(char	*cmd)
{
	char	*file = "/bin/bash";
	char	*const args[] = {file, "-c", cmd, NULL};
	char	*const env[] =  {NULL};
	execve(file, args, env);
}

int	main(int argc, char **argv)
{
	int	fd;
	int	bytes_read;

	if (argc == 5)
	{
