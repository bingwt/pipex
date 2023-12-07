/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:59:51 by btan              #+#    #+#             */
/*   Updated: 2023/12/07 13:24:01 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <libft.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

# ifndef READ_END
#  define READ_END	0
# endif

# ifndef WRITE_END
#  define WRITE_END	1
# endif

typedef struct	properties
{
	char	*cmd;
	char	*temp;
	char	**args;
}	t_props;
#endif
