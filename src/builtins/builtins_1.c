/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:29:46 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/17 12:24:27 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_glob	g_global;


int	builtins(t_prompt *prompt, t_list *cmd, int *is_exit, int n)
{
	char **a;

	while (cmd)
	{
		a = ((t_input *)cmd->content)->full_cmd;
		n = 0;
		if (a)
			n = ft_strlen(*a);
		if (a && !ft_strncmp(*a, "exit", n) && n == 4)
			g_global.g_state = ft_exit(cmd, is_exit);
		else if (!cmd->next && a && !ft_strncmp(*a, "cd", n) && n == 2)
			g_global.g_state = ft_cd(prompt);
		else if (!cmd->next && a && !ft_strncmp(*a, "export", n) && n == 6)
			g_global.g_state = ft_export(prompt);
		else if (!cmd->next && a && !ft_strncmp(*a, "unset", n) && n == 5)
			g_global.g_state = ft_unset(prompt);
		else
		{
			//signal(SIGINT, handle_sigint_cmd);
			//signal(SIGQUIT, SIG_IGN);
			exec_cmd(prompt, cmd);
		}
		cmd = cmd->next;
	}
	return (g_global.g_state);
}

int is_builtins(t_input *node)
{
	int	l;

	if (!node->full_cmd)
		return (0);
	if ((node->full_cmd && ft_strchr(*node->full_cmd, '/')) || (node->full_path && \
		ft_strchr(node->full_path, '/')))
		return (0);
	l = ft_strlen(*node->full_cmd);
	if (!ft_strncmp(*node->full_cmd, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "exit", l) && l == 4)
		return (1);
	return (0); 
}
int	ft_cd(t_prompt *p)
{
	char	**str[2];
	char	*aux;

	g_global.g_state = 0;
	str[0] = ((t_input *)p->cmds->content)->full_cmd;
	aux = ft_getenv("HOME", p->envp, 4);
	if (!aux)
		aux = ft_strdup("", &g_global.gc);
	str[1] = ft_extend_matrix(NULL, aux);
	cd_error(str);
	if (!g_global.g_state)
		p->envp = ft_setenv("OLDPWD", str[1][1], p->envp, 6);
	aux = getcwd(NULL, 0);
	if (!aux)
		aux = ft_strdup("", &g_global.gc);
	str[1] = ft_extend_matrix(str[1], aux);
	free(aux);
	p->envp = ft_setenv("PWD", str[1][2], p->envp, 3);
	ft_free_matrix(&str[1]);
	return (g_global.g_state);
}

int	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 4096);
	printf("buf = [%s]\n", buf);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}

int	ft_echo(t_list *cmd)
{
	int	nl;
	int	i[2];
	char **argv;
	t_input *node;

	i[0] = 0;
	i[1] = 0;
	nl = 1;
	node = cmd->content;
	argv = node->full_cmd;
	while (argv && argv[++i[0]])
	{
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2) && \
			(ft_countchar(argv[i[0]], 'n') == \
			(int)(ft_strlen(argv[i[0]]) - 1)))
			nl = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(argv[i[0]], 1);
			if (argv[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	return (write(1, "\n", nl) == 2);
}
