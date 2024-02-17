/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:08:20 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/17 12:38:14 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_glob g_global;

void	ft_free_matrix(char ***m)
{
	int	i;

	i = 0;
	while (m && m[0] && m[0][i])
		i++;
	if (m)
		*m = NULL;
}

char	**ft_extend_matrix(char **in, char *newstr)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!newstr)
		return (in);
	len = ft_matrixlen(in);
	out = gc_malloc(&g_global.gc, sizeof(char *) * (len + 2));
	out[len + 1] = NULL;
	if (!out)
		return (in);
	while (++i < len)
	{
		out[i] = ft_strdup(in[i], &g_global.gc);
		if (!out[i])
		{
			ft_free_matrix(&in);
			ft_free_matrix(&out);
		}
	}
	out[i] = ft_strdup(newstr, &g_global.gc);
	ft_free_matrix(&in);
	return (out);
}

int	ft_matrixlen(char **m)
{
	int	i;

	i = 0;
	while (m && m[i])
		i++;
	return (i);
}

char	**ft_matrix_replace_in(char ***big, char **small, int n)
{
	char	**aux;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!big || !*big || n < 0 || n >= ft_matrixlen(*big))
		return (NULL);
	aux = ft_calloc(ft_matrixlen(*big) + ft_matrixlen(small), sizeof(char *), &g_global.gc);
	while (aux && big[0][++i[0]])
	{
		if (i[0] != n)
			aux[++i[2]] = ft_strdup(big[0][i[0]], &g_global.gc);
		else
		{
			while (small && small[++i[1]])
				aux[++i[2]] = ft_strdup(small[i[1]], &g_global.gc);
		}
	}
	ft_free_matrix(big);
	*big = aux;
	return (*big);
}

int	ft_putmatrix_fd(char **m, int nl, int fd)
{
	int	i;
	int	count;
	int	lenm;

	count = 0;
	i = 0;
	while (m && m[i])
	{
		if (m[i])
			lenm = ft_strlen(m[i] + 1);
		else
			lenm = 0;
		if (nl)
		{
			ft_putendl_fd(m[i], fd);
			count += lenm;
		}
		else
		{
			ft_putstr_fd(m[i], fd);
			count += lenm;
		}
		i++;
	}
	return (count);
}
