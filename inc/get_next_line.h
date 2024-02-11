/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:02:32 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/11 17:48:13 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

/**structure**/
typedef struct s_data
{
	int		fd;
	int		newline_index;
	char	*buf;
	char	*tmp;
	ssize_t	buf_size;
}	t_data;

/**main functions**/
char	*get_next_line(int fd);
char	*concatenate_bufer(char *stock, char *buf);
char	*get_stock_after_newline(char *stock);
int		get_newline_index(char *stock);
/**utils functions**/
ssize_t	ft_strlen_gnl(char *str);
int		read_until_nl(t_data *datas, char **stock);
#endif