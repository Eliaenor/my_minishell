/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 20:38:24 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/13 20:38:26 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

void		check_right(char **path, char **args, t_data *data)
{
	struct stat		stats;

	if (stat(*path, &stats) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(args[1]);
		*path = get_var_env(data, "PWD=");
	}
	else if ((stats.st_mode & S_IRUSR) == 0)
	{
		ft_putstr("cd: permission denied: ");
		ft_putendl(args[1]);
		*path = get_var_env(data, "PWD=");
	}
	else if ((stats.st_mode & S_IFDIR) == 0)
	{
		ft_putstr("cd: not a directory: ");
		ft_putendl(args[1]);
		*path = get_var_env(data, "PWD=");
	}
}

void		check_right_exec(char **path, char **args)
{
	struct stat		stats;

	if (stat(*path, &stats) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(args[0]);
		*path = NULL;
	}
	else if ((stats.st_mode & S_IXUSR) == 0)
	{
		ft_putstr("cd: permission denied: ");
		ft_putendl(args[0]);
		*path = NULL;
	}
}
