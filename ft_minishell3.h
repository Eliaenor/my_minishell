/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell3.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/23 05:03:04 by vcourtin          #+#    #+#             */
/*   Updated: 2013/12/23 05:03:07 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "./libft/includes/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# define UP			0
# define DOWN		1
# define PROMPT		"A ton service Bill.% "

typedef struct dirent t_dirent;

typedef struct	s_data
{
	char		**environ;
	int			test;
	int			i;
	char		*path;
	char		*abspath1;
	int			nbrofpipes;
	int			fd_history;
	int			history_last;
	int			line;
	int			first_history;
}				t_data;

/*
** main **
*/

int		ft_get_entry(t_data *data);
int		ft_test(t_data *data, char *buff, int j);
char	*ft_test3(t_data *data, char *buff, int *j, char *stdin);
int		ft_test2(t_data *data, char *buff, int j, char *stdin);

/*
** arrow **
*/

int		up_arrow(t_data *data, int j, char *buff);
int		down_arrow(t_data *data, int j, char *buff);
int		left_arrow(int j);
int		right_arrow(int j, char *buff, t_data *data);

/*
** changedir **
*/

void	ft_changedirectory(t_data *data, char **args);
void	ft_change_part2(char *env_pwd, t_data *data);
int		change_pwd(t_data *data, char *var);

/*
** check **
*/

void	check_right(char **path, char **args, t_data *data);
void	check_right_exec(char **path, char **args);

/*
** env1 **
*/

char	*get_var_env(t_data *data, char *varenv);
char	**ft_addto_env(t_data *data, char *newvar);
int		set_var_env(t_data *data, char *varenv);
int		ft_delto_env(t_data *data, char *nameofvar);
int		delto_env_part2(t_data *data, char *name, int len, char ***newenv);

/*
** env2 **
*/

int		ft_setenv(t_data *data, char *varname, char *var);
int		ft_aff_env(t_data *data);

/*
** choice **
*/

void	ft_choice(char **args, t_data *data);
void	ft_choice_part2(char **args, t_data *data);
void	ft_choice_part3(char **args, t_data *data);
void	ft_choice_part4(char **args, t_data *data);

/*
** function **
*/

int		**init_tab(int **tbl);
int		ft_exec(t_data *data, char **args);
int		ft_search(char **args, t_data *data);

/*
** lib **
*/

char	**ft_split_once(char *str, char c);
char	**ft_split_once_part2(char **tbl, char *str, char c);
char	**ft_tabdup(char **tbl1);
void	ft_free_env(char **environ);
void	create_var_env(t_data *data, char *nameofvar);

/*
** test **
*/

void	ft_put_double_tab(char **tbl);
int		ft_parseur(char *str, t_data *data);

/*
** term **
*/
int		ft_outc(int c);
int		init_term(t_data *data);
int		reset_term(t_data *data);
int		ft_putstr_term(char *str, t_data *data);

/*
** signal **
*/

int		ft_init_global(t_data *data);
void	sig_ctrl_c(int n);

/*
** edit_tab **
*/

char	*add_to_tab(char *tbl, char c, int pos);
char	*ft_delete(int j, char *buff);

/*
** get_line **
*/

char	*get_next_line_m(int fd);
char	*get_prev_line(int fd, t_data *data);
char	*ft_miniread(char *line, char *buff, t_data *data, int fd);

/*
** delete_buff **
*/

int		delete_cmd(t_data *data, int j);
int		back_to_j(char *buff, int j);
int		ft_del_line(t_data *data, int curent_line);

/*
** key **
*/

char	*ascii_key(t_data *data, char *buff, char *stdin, int j);
int		ft_mini_enter(t_data *data, char *buff);
int		arrow_key(t_data *data, char *buff, int j, char *stdin);
int		enter_key(t_data *data, char *buff);
int		escape_key(t_data *data, char *buff, int j, char *stdin);

/*
** ctrl **
*/

int		ft_ctrl(t_data *data, char *buff, int j);
int		goto_nextword(char *buff, int j, t_data *data);

#endif
