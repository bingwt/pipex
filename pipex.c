/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:27:40 by btan              #+#    #+#             */
/*   Updated: 2023/11/07 17:39:22 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.a"
#include <unistd.h>

char	*rd_left(char *content);
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
