/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:29:43 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/17 12:24:27 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_glob	g_global;


char	*get_here_str(char *s[2], size_t len, char *limit, char *warn)
{
	char	*temp;

	while (g_global.g_state != 130 && (!s[0] || ft_strncmp(s[0], limit, len) \
		|| ft_strlen(limit) != len))
	{
		temp = s[1];
		s[1] = ft_strjoin(s[1], s[0], &g_global.gc);
		s[0] = readline("> ");
		if (!s[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		temp = s[0];
		s[0] = ft_strjoin(s[0], "\n", &g_global.gc);
		len = ft_strlen(s[0]) - 1;
	}
	return (s[1]);
}

int	get_here_doc(char *s[2], char *aux[2])
{
	int		fd[2];

	g_global.g_state = 0;
	if (pipe(fd) == -1)
	{
		ft_perror(PIPE_ERR, NULL, 1);
		return (-1);
	}
	s[1] = get_here_str(s, 0, aux[0], aux[1]);
	write(fd[WRITE_END], s[1], ft_strlen(s[1]));
	// free(s[1]);
	close(fd[WRITE_END]);
	if (g_global.g_state == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
