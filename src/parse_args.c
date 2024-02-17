/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:31:58 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/17 12:24:27 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_glob	g_global;

static char **split_all(char **args, t_prompt *prompt)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, prompt);
		args[i] = expand_path(args[i], -1, quotes, \
			ft_getenv("HOME", prompt->envp, 4));
		subsplit = ft_cmdsubsplit(args[i], "<|>");
		ft_matrix_replace_in(&args, subsplit, i);
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	return (args);
}

static void	*parse_args(char **args, t_prompt *p)
{
	int	is_exit;
	int	i;

	is_exit = 0;
	p->cmds = fill_nodes(split_all(args, p), -1);
	if (!p->cmds)
		return (p);
	i = ft_lstsize(p->cmds);
	g_global.g_state = builtins(p, p->cmds, &is_exit, 0);
	while (i-- > 0)
		waitpid(-1, &g_global.g_state, 0);
	if (!is_exit && g_global.g_state == 13)
		g_global.g_state = 0;
	if (g_global.g_state > 255)
		g_global.g_state = g_global.g_state / 255;
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}
	return (p);
}

void	*check_args(char *out, t_prompt *p)
{
	char	**a;
	t_input	*n;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	a = ft_cmdtrim(out, " ");
	if (!a)
		ft_perror(QUOTE, NULL, 1);
	if (!a)
		return ("");
	p = parse_args(a, p);
	if (p && p->cmds)
		n = p->cmds->content;
	if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
		p->envp = ft_setenv("_", n->full_cmd[ft_matrixlen(n->full_cmd) - 1], \
			p->envp, 1);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
