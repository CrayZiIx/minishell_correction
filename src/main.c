/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:12:49 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/12 18:26:13 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

struct {
	int state;
	t_gcan gc;
}	g_state;

extern int		g_state;

/*DESCRPTION*/
//ft_getpid is a fct who take a pointer on a t_prompt struct, this function define prompt->pid using waitpid
static void		ft_getpid(t_prompt *prompt)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_perror(FORK_ERR, NULL, 1);
		ft_free_matrix(&prompt->envp);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&prompt->envp);
		exit(1);	
	}
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

static t_prompt	init_var(t_prompt prompt, char *s, char **argv)
{
	char	*num;

	s = getcwd(NULL, 0);
	prompt.envp = ft_setenv("PWD", s, prompt.envp, 3);
	free(s);
	s = ft_getenv("SHLVL", prompt.envp, 5);
	if (!s || ft_atoi(s) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(s) + 1);
	free(s);
	prompt.envp = ft_setenv("SHLVL", num, prompt.envp, 5);
	free(num);
	s = ft_getenv("PATH", prompt.envp, 4);
	// if (!s)
	// 	prompt.envp = ft_setenv("PATH", \
	// 	"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	// free(s);
	s = ft_getenv("_", prompt.envp, 1);
	if (!s)
		prompt.envp = ft_setenv("_", argv[0], prompt.envp, 1);
	free(s);
	return (prompt);
}

static t_prompt	init_prompt(char **argv, char **envp)
{
	t_prompt	prompt;
	char		*s;

	s = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	g_state = 0;
	ft_getpid(&prompt);
	prompt = init_var(prompt, s, argv);
	return (prompt);
}

int				main(int ac, char **av, char **envp)
{
	char		*out;
	t_prompt	prompt;

	gc_init(&g_state.gc);
	prompt = init_prompt(av, envp);
	while (av && ac)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		out = readline("guest@minishell $ ");
		if (!check_args(out, &prompt))
			break ;
	}
	gc_clean(&g_state.gc);
	exit(g_state);
}
