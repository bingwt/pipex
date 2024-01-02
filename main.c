/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 03:05:11 by btan              #+#    #+#             */
/*   Updated: 2024/01/02 17:59:54 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char **argv, char **envp)
{
//	char	*path;

//	path = get_path(envp, "catd");
//	ft_printf("main: %s\n", path);
//	if (path)
//		free(path);
	if (argc != 5)
	{
		ft_printf_fd(2, "Please provide 4 arguments!\n");
		return (1);
	}
	pipex(argv, envp);
	return (0);
}
