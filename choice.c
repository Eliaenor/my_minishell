/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/27 17:34:44 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/27 17:34:47 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

void		ft_choice(char **args, t_data *data)
{
	struct stat		stats;

	if (ft_strcmp(args[0], "env") == 0 || ft_strcmp(args[0], "setenv") == 0)
		ft_choice_part2(args, data);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_choice_part4(args, data);
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		ft_delto_env(data, args[1]);
	else if (args[0][0] == '.' && args[0][1] == '/')
		ft_choice_part3(args, data);
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		data->test++;
		tputs(tgetstr("te", NULL), 0, ft_outc);
		exit(0);
	}
	else if (stat(data->path, &stats) == 0)
		ft_exec(data, args);
}

void		ft_choice_part2(char **args, t_data *data)
{
	if (ft_strcmp(args[0], "env") == 0)
		ft_aff_env(data);
	else if (ft_strcmp(args[0], "setenv") == 0)
		ft_setenv(data, args[1], args[2]);
}

void		ft_choice_part3(char **args, t_data *data)
{
	char		*tmp;

	tmp = NULL;
	if (args[0][0] == '.' && args[0][1] == '/')
	{
		data->path = ft_strjoin(ft_strjoin(getcwd(tmp, 1024), "/"),
						args[0] + 2);
		args[0] = args[0] + 2;
		check_right_exec(&(data->path), args);
		if (data->path != NULL)
			ft_exec(data, args);
		free(tmp);
		data->test++;
	}
}

void		ft_choice_part4(char **args, t_data *data)
{
	if (ft_strcmp(args[0], "cd") == 0)
	{
		ft_changedirectory(data, args);
		change_pwd(data, "PWD");
		data->test++;
	}
}
