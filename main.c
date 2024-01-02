/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 03:05:11 by btan              #+#    #+#             */
/*   Updated: 2024/01/02 12:35:39 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char **argv, char **envp)
{
	char	*path;

	path = get_path(envp, "cat");
	ft_printf("main: %s\n", path);
	free(path);
	if (argc != 5)
	{
		ft_printf("Please provide 4 arguments!\n");
		return (1);
	}
	pipex(argv[1], argv[2], argv[3], argv[4], envp);
	return (0);
}
