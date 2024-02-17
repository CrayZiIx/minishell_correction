/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:04:33 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/17 12:27:06 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_glob	g_global;

void	*ft_perror(int err_type, char *param, int err)
{
	g_global.g_state = err;
	if (err_type == QUOTE)
		ft_putstr_fd("Error: missing quote !\n", 2);
	else if (err_type == NO_DIR)
		ft_putstr_fd("Error: bro, this directory doesn't exist !\n", 2);
	else if (err_type == NO_PERM)
		ft_putstr_fd("Error: ask ur mom before using this !\n", 2);
	else if (err_type == NOT_CMD)
		ft_putstr_fd("Error: bro, can u please type a real cmd !\n", 2);
	else if (err_type == DUP_ERR)
		ft_putstr_fd("Error: bro, dup2 failed ...\n", 2);
	else if (err_type == FORK_ERR)
		ft_putstr_fd("Error: bro, fork failed sorry !\n", 2);
	else if (err_type == PIPE_ERR)
		ft_putstr_fd("Error: bro, wtf  !\n", 2);
	else if (err_type == PIPES_ERR)
		ft_putstr_fd("Error: bro, pfff !\n", 2);
	else if (err_type == MEM)
		ft_putstr_fd("Error: bro, mem this directory doesn't exist !\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("Error: bro, is dir this directory doesn't exist !\n", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("Error: bro, maybe is the way !\n", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}

int	ft_atoi2(const char *nptr, long *nbr)
{
	int	sign;

	sign = 1;
	*nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		sign = -sign;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (!ft_isdigit(*nptr))
		return (-1);
	while (ft_isdigit(*nptr))
	{
		*nbr = 10 * *nbr + (*nptr - '0');
		nptr++;
	}
	if (*nptr && !ft_isspace(*nptr))
		return (-1);
	*nbr *= sign;
	return (0);
}

int	ft_exit(t_list *cmd, int *is_exit)
{
	t_input	*node;
	long	status[2];

	node = cmd->content;
	*is_exit = !cmd->next;
	if (*is_exit)
		ft_putstr_fd("exit\n", 2);
	if (!node->full_cmd || !node->full_cmd[1])
		return (0);
	status[1] = ft_atoi2(node->full_cmd[1], &status[0]);
	if (status[1] == -1)
	{
		ft_putstr_fd("minishell exit: ", 2);
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd(" : numeric args needed", 2);
		return (255);
	}
	else if (node->full_cmd[2])
	{
		*is_exit = 0;
		ft_putstr_fd("minishell: exit: too many args\n", 2);
		return (1);
	}
	status[0] %= 256 + 256 * (status[0] < 0);
	return (status[0]);
}

void	cd_error(char **s[2])
{
	DIR	*dir;

	dir = NULL;
	if (s[0][1])
		dir = opendir(s[0][1]);
	if (!s[0][1] && s[1][0] && !s[1][0][0])
	{
		g_global.g_state = 1;
		ft_putstr_fd("minishell: error: HOME not set !\n", 2);
	}
	if (s[1][0] && !s[0][1])
		g_global.g_state = chdir(s[1][0]) == -1;
	if (s[0][1] && dir && access(s[0][1], F_OK) != -1)
		chdir(s[0][1]);
	else if (s[0][1] && access(s[0][1], F_OK) == -1)
		ft_perror(NOT_DIR, s[0][1], 1);
	else if (s[0][1])
		ft_perror(NOT_DIR, s[0][1], 1);
	if (s[0][1] && dir)
		closedir(dir);
}

void	free_content(void *content)
{
	t_input	*node;

	node = content;
	ft_free_matrix(&node->full_cmd);
	if (node->pipein != STDIN_FILENO)
		close(node->pipein);
	if (node->pipeout != STDOUT_FILENO)
		close(node->pipeout);
}
