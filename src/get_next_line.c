/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:02:30 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/11 18:00:57 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"
#include "../inc/minishell.h"

char	*get_next_line(int fd)
{
	static char	*stock;
	t_data		datas;
	int			status;

	datas.fd = fd;
	if (datas.fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	datas.buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	status = read_until_nl(&datas, &stock);
	if (status == 0)
		return (NULL);
	if (status == 1)
		return (datas.tmp);
	datas.tmp = stock;
	free(datas.buf);
	stock = get_stock_after_newline(stock + datas.newline_index + 1);
	datas.tmp[datas.newline_index + 1] = '\0';
	return (datas.tmp);
}

char	*concatenate_bufer(char *stock, char *buf)
{
	char	*ret;
	int		i;
	int		y;

	ret = malloc(sizeof(char) * (ft_strlen_gnl(stock) + ft_strlen_gnl(buf) + 1));
	i = 0;
	if (stock != NULL)
	{
		while (stock[i])
		{
			ret[i] = stock[i];
			i++;
		}
	}
	y = 0;
	while (buf[y])
	{
		ret[i + y] = buf[y];
		y++;
	}
	ret[i + y] = '\0';
	free(stock);
	return (ret);
}

int	get_newline_index(char *stock)
{
	int	i;

	i = 0;
	if (stock == NULL)
		return (-1);
	while (stock[i])
	{
		if (stock[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_stock_after_newline(char *stock)
{
	char	*ret;
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen_gnl(stock);
	if (len == 0)
		return (NULL);
	ret = malloc(sizeof(char) * (len + 1));
	while (stock[i] != '\0')
	{
		ret[i] = stock[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
