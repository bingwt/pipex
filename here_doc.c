/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:19:11 by btan              #+#    #+#             */
/*   Updated: 2024/01/03 16:55:16 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

void	here_doc(char *eof)
{
	int		fd;
	char	*buffer;

	fd = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(0);
		if (!ft_strncmp(buffer, eof, ft_strlen(eof)))
			break ;
		ft_printf_fd(fd, "%s", buffer);
	}
	if (buffer)
		free(buffer);
	close(fd);
	fd = open("here_doc.tmp", O_RDONLY);
	buffer = get_next_line(fd);
	while (buffer)
	{
		ft_printf("%s", buffer);
		free(buffer);
		buffer = get_next_line(fd);
	}
	unlink("here_doc.tmp");
}
