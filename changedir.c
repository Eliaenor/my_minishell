/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 20:42:18 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/13 20:42:25 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

void		ft_changedirectory(t_data *data, char **args)
{
	char	*env_pwd;
	char	*path;

	env_pwd = ft_strjoin(get_var_env(data, "PWD="), "/");
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		ft_change_part2(env_pwd, data);
	else if (args[1])
	{
		path = ft_strjoin(env_pwd, args[1]);
		check_right(&path, args, data);
		change_pwd(data, "OLD");
		path = (args[1][0] == '/' ? args[1] : path);
		chdir(path);
	}
	else
	{
		path = get_var_env(data, "HOME=");
		change_pwd(data, "OLD");
		chdir(path);
	}
	free(env_pwd);
}

void		ft_change_part2(char *env_pwd, t_data *data)
{
	char	*path;

	path = ft_strjoin(env_pwd, get_var_env(data, "OLDPWD"));
	ft_putendl(get_var_env(data, "OLDPWD="));
	change_pwd(data, "OLD");
	chdir(path);
}

int			change_pwd(t_data *data, char *var)
{
	char	*tmp;
	int		buffsize;
	char	*pwd;

	tmp = NULL;
	if (ft_strcmp(var, "OLD") == 0)
	{
		buffsize = ft_strlen(get_var_env(data, "PWD=")) + 256;
		tmp = getcwd(tmp, buffsize);
		pwd = ft_strjoin("OLDPWD=", tmp);
		free(tmp);
		set_var_env(data, pwd);
		free(pwd);
	}
	else if (ft_strcmp(var, "PWD") == 0)
	{
		buffsize = ft_strlen(get_var_env(data, "PWD=")) + 256;
		tmp = getcwd(tmp, buffsize);
		pwd = ft_strjoin("PWD=", tmp);
		free(tmp);
		set_var_env(data, pwd);
		free(pwd);
	}
	return (0);
}
