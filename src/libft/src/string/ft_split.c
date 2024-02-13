/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:04:48 by liguyon           #+#    #+#             */
/*   Updated: 2024/02/13 19:14:50 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_iter(char **res, int index, void *gc)
{
	while (--index >= 0)
		gc_free(gc, (void **)&res[index]);
	gc_free(gc, (void **)&res);
	return (NULL);
}

static char	**make_array_split(char const *s, char c, void *gc)
{
	int		i;
	int		size;
	char	**res;

	size = 0;
	i = -1;
	while (s[++i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		size++;
		if (!ft_strchr(&s[i], c))
			break ;
		i += (ft_strchr(&s[i], c) - &s[i]) - 1;
	}
	res = gc_malloc(gc, sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	res[size] = NULL;
	return (res);
}

static char	**ft_split_alt(char const *s, char c, char **res, void *gc)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (s[++i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		if (!ft_strchr(&s[i], c))
		{
			res[++j] = ft_strdup(&s[i], gc);
			if (!res[j])
				return (ft_free_iter(res, j, gc));
			break ;
		}
		res[++j] = ft_substr(s, i, ft_strchr(&s[i], c) - &s[i], gc);
		if (!res[j])
			return (ft_free_iter(res, j, gc));
		i += ft_strchr(&s[i], c) - &s[i] - 1;
	}
	return (res);
}

char	**ft_split(char const *s, char c, void *gc)
{
	char	**res;

	if (!s)
		return (NULL);
	res = make_array_split(s, c, gc);
	if (!res)
		return (NULL);
	return (ft_split_alt(s, c, res, gc));
}
