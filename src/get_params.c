/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:26:58 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/17 12:42:09 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_glob	g_global;

void	print_error_heredoc(char c, int *i)
{
	if (c == '<')
		ft_putendl_fd("minishell: syntax error near unexpected token '<' or '<<'", 2);
	else if (c == '>')
		ft_putendl_fd("minishell: syntax error near unexpected token '>' or '>>'", 2);
	else
		ft_putendl_fd("minishell: syntax error near unexpected token 'newline", 2);
	g_global.g_state = 2;
	(*i) = -2;
}
int	get_fd(int oldfd, char *path, int flags[2])
{
	int fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		ft_perror(NOT_DIR, path, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		ft_perror(NO_PERM, path, 126);
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666 );
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666 );
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_input	*get_pipeout1(t_input *node, char **args, int *i)
{
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	(*i)++;
	if (args[*i])
		node->pipeout = get_fd(node->pipeout, args[*i], flags);
	if (!args[*i] || node->pipeout == -1)
	{
		*i = -1;
		if (node->pipeout != -1)
			print_error_heredoc('0', i);
		else
			g_global.g_state = 1;
	}
	return (node);
}

t_input *get_pipeout2(t_input *node, char **args, int *i)
{
	int	flags[2];

	flags[0] = 1;
	flags[1] = 0;
	(*i)++;
	if (args[3] && args[3][0] == '<')
	{
		print_error_heredoc('<', i);
		return (node);
	}
	if (args[++(*i)])
		node->pipeout = get_fd(node->pipeout, args[*i], flags);
	if (!args[*i] || node->pipeout == -1)
	{
		*i = -1;
		if (node->pipeout != -1)
		{
			print_error_heredoc('0', i);
		}
		else
			g_global.g_state = 1;
	}
	return (node);
}

t_input *get_pipein1(t_input *node, char **args, int *i)
{
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	(*i)++;
	if (args[*i])
		node->pipein = get_fd(node->pipein, args[*i], flags);
	if (!args[*i] || node->pipein == -1)
	{
		*i = -1;
		if (node->pipein != -1)
			print_error_heredoc('0', i);
		else
			g_global.g_state = 1;
	}
	return (node);
}

t_input *get_pipein2(t_input *node, char **args, int *i)
{
	char	*aux[2];
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	(*i)++;
	if (args[3] && args[3][0] == '>')
	{
		print_error_heredoc('>', i);
		return (node);
	}
	if (args[++(*i)])
	{
		aux[0] = args[*i];
		node->pipein = get_here_doc(str, aux);
	}
	if (!args[*i] || node->pipein == -1)
	{
		*i = -1;
		if (node->pipein != -1)
			print_error_heredoc('0', i);
	}
	return (node);}
