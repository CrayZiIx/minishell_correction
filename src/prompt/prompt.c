/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:33:15 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/17 12:24:27 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_glob	g_global;


static char		*get_home(t_prompt prompt)
{
	char	*temp;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("SDF", &g_global.gc);
	home = ft_getenv("HOME", prompt.envp, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(home)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)], &g_global.gc);
		// free(temp);
	}
	free(pwd);
	pwd = ft_strjoin(home , " ", &g_global.gc);
	// free(home);
	home = ft_strjoin(" ", pwd, &g_global.gc);
	// free(home);
	return(pwd);
}

// static char	*get_user(t_prompt prompt)
// {
// 	char	**user;
// 	char	*temp;
// 	char	*temp2;

// 	user = NULL;
// 	temp2 = NULL;
// 	exec_custom(&user, "/usr/bin/whoami", "whoami", prompt.envp);
// 	if (!user)
// 		user = ft_extend_matrix(user, "guest");
// 	if (!ft_strncmp(user[0], "root", 4))
// 		temp2 = ft_strjoin(NULL, RED);
// 	else if ((int)(user[0][0]) % 5 == 0)
// 		temp2 = ft_strjoin(NULL, CYAN);
// 	else if ((int)(user[0][0]) % 5 == 1)
// 		temp2 = ft_strjoin(NULL, GRAY);
// 	else if ((int)(user[0][0]) % 5 == 2)
// 		temp2 = ft_strjoin(NULL, GREEN);
// 	else if ((int)(user[0][0]) % 5 == 3)
// 		temp2 = ft_strjoin(NULL, MAGENTA);
// 	else
// 		temp2 = ft_strjoin(NULL, YELLOW);
// 	temp = ft_strjoin(temp2, *user);
// 	free(temp2);
// 	ft_free_matrix(&user);
// 	return (temp);
// }

// char	*ft_getprompt(t_prompt prompt)
// {
// 	char	*temp;
// 	char	*temp2;
// 	char	*aux;

// 	temp = """
// 	// temp2 = ft_strjoin(temp, "@minishell");
// 	free(temp);
// 	aux = get_home(prompt);
// 	temp = ft_strjoin(temp2, aux);
// 	free(aux);
// 	free(temp2);
// 	// if (!g_global.g_state || g_global.g_state == -1)
// 	// 	temp2 = ft_strjoin(temp, BLUE);
// 	// else
// 	// 	temp2 = ft_strjoin(temp, RED);
// 	free(temp);
// 	temp = ft_strjoin(temp2, "$ ");
// 	// free(temp2);
// 	// temp2 = ft_strjoin(temp, DEFAULT);
// 	free(temp);
// 	return (temp2);
// }