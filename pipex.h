/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:59:51 by btan              #+#    #+#             */
/*   Updated: 2023/12/19 17:10:47 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <libft.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

void	pipex(char *infile, char *cmd1, char *cmd2, char *outfile);
#endif
