/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:59:51 by btan              #+#    #+#             */
/*   Updated: 2023/11/27 14:17:12 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <libft.h>
# include <stdio.h>

typedef struct	properties
{
	char	*cmd;
	char	*temp;
	char	**args;
}	t_props;
#endif
