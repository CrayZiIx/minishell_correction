/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:30:01 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/17 12:24:27 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_glob g_global;

char	**ft_dup_matrix(char **m)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	n_rows = ft_matrixlen(m);
	out = gc_malloc(&g_global.gc, sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	while (m[i])
	{
		out[i] = ft_strdup(m[i], &g_global.gc);
		if (!out[i])
		{
			ft_free_matrix(&out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}