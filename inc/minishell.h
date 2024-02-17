/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:58:29 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/17 13:15:28 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

/*------------*/
/*--INCLUDES--*/
/*------------*/
# include "../src/gc/gc.h"
# include "../src/libft/libft.h"
# include "./get_next_line.h"
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

# define READ_END 0
# define WRITE_END 1

/*--------------*/
/*--STRUCTURES--*/
/*--------------*/
typedef struct s_glob
{
	t_gcan	gc;
	int		g_state;
}				t_glob;

typedef struct s_prompt
{
	t_list		*cmds;
	char		**envp;
	pid_t		pid;
}				t_prompt;

typedef struct s_input
{
	char	**full_cmd;
	char	*full_path;
	int		pipein;
	int		pipeout;
}				t_input;
/*---------*/
/*--TYPES--*/
/*---------*/

typedef enum e_rl_error
{
	QUOTE = 1,
	NO_DIR,
	NO_PERM,
	NOT_CMD,
	DUP_ERR,
	FORK_ERR,
	PIPE_ERR,
	PIPES_ERR,
	MEM,
	IS_DIR,
	NOT_DIR
}				t_rl_error;
/*---------*/
/*FUNCTIONS*/
/*---------*/
/*--[exec.c]--*/
void	*check_to_fork(t_prompt *prompt, t_list *cmd, int fd[2]);
/*--[signal.c]--*/
void	handle_sigint_cmd(int sig);
void	handle_sigint(int sig);
/*--[error.c]--*/
void	*ft_perror(int err_type, char *param, int err);
int		ft_exit(t_list *cmd, int *is_exit);
void	free_content(void *content);
void	cd_error(char **s[2]);
/*--[builtins_1.c]--*/
int		builtins(t_prompt *prompt, t_list *cmd, int *is_exit, int n);
int		is_builtins(t_input *node);
int		ft_pwd(void);
int		ft_echo(t_list *cmd);
int		ft_cd(t_prompt *p);
/*--[utils_1.c]--*/
int		ft_countchar(char *s, char c);
int		ft_strchr_i(const char *s, int c);
int		ft_strchars_i(const char *s, char *set);
/*--[ft_matrix.c]--*/
void	ft_free_matrix(char ***m);
char	**ft_extend_matrix(char **in, char *newstr);
int		ft_matrixlen(char **m);
char	**ft_matrix_replace_in(char ***big, char **small, int n);
int		ft_putmatrix_fd(char **m, int nl, int fd);
/*--[ft_matrix_2.c]--*/
char	**ft_dup_matrix(char **m);
/*--[ft_strtrim_all.c ]--*/
char	*ft_strtrim_all(char const *s1, int squote, int dquote);
/*--[heredoc.c]*/
int		get_here_doc(char *s[2], char *aux[2]);
/*--[env.c]--*/
char	*ft_getenv(char *var, char **envp, int n);
char	**ft_setenv(char *var, char *value, char **envp, int n);
int		ft_export(t_prompt *prompt);
int		ft_unset(t_prompt *prompt);
/*--[get_params.c ]--*/
int		get_fd(int oldfd, char *path, int flags[2]);
t_input	*get_pipeout1(t_input *node, char **args, int *i);
t_input	*get_pipeout2(t_input *node, char **args, int *i);
t_input	*get_pipein1(t_input *node, char **args, int *i);
t_input	*get_pipein2(t_input *node, char **args, int *i);
/*--[get_cmd.c]--*/
void	*exec_cmd(t_prompt *prompt, t_list *cmd);
/*--[expend.c]--*/
char	*expand_path(char *s, int i, int quotes[2], char *var);
char	*expand_vars(char *s, int i, int quotes[2], t_prompt *prompt);
/*--[ft_cmdsubsplit.c ]--*/
char	**ft_cmdsubsplit(char const *s, char *set);
/*--[ft_cmdsubsplit.c ]--*/
char	**ft_cmdtrim(char const *s, char *set);
/*--[fill_nodes.c]--*/
t_list	*fill_nodes(char **args, int i);
/*--[parse_args.c]--*/
void	*check_args(char *out, t_prompt *p);

// char	*ft_getprompt(t_prompt prompt);
void	*my_ptr(void *init_ptr);


#endif