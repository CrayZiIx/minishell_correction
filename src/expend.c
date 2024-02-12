/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 04:44:47 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/12 16:30:02 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_state;

char	*expand_path(char *s, int i, int quotes[2], char *var)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (s && s[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && s[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && s[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && s[i] == '~' && (i == 0 || \
			s[i - 1] != '$'))
		{
			aux = ft_substr(s, 0, i);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(s, i + 1, ft_strlen(s));
			free(s);
			s = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (expand_path(s, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (s);
}

static char	*get_substr_var(char *s, int i, t_prompt *prompt)
{
	char	*aux;
	int		pos;
	char	*path;
	char	*var;

	pos = ft_strchars_i(&s[i], "|\"\'$?>< ") + (ft_strchr("$?", s[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(s) - 1;
	aux = ft_substr(s, 0, i - 1);
	var = ft_getenv(&s[i], prompt->envp, \
		ft_strchars_i(&s[i], "\"\'$|>< "));
	if (!var && s[i] == '$')
		var = ft_itoa(prompt->pid);
	else if (!var && s[i] == '?')
		var = ft_itoa(g_state);
	path = ft_strjoin(aux, var);
	free(aux);
	aux = ft_strjoin(path, &s[i + pos]);
	free(var);
	free(path);
	free(s);
	return (aux);
}

char	*expand_vars(char *s, int i, int quotes[2], t_prompt *prompt)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (s && s[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && s[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && s[i] == '\"')) % 2;
		if (!quotes[0] && s[i] == '$' && s[i + 1] && \
			((ft_strchars_i(&s[i + 1], "/~%^{}:; ") && !quotes[1]) || \
			(ft_strchars_i(&s[i + 1], "/~%^{}:;\"") && quotes[1])))
			return (expand_vars(get_substr_var(s, ++i, prompt), -1, \
				quotes, prompt));
	}
	return (s);
}