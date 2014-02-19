/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/27 17:35:52 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/27 17:36:19 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

int			**init_tab(int **tbl)
{
	int		i;

	i = 0;
	while (tbl[i])
	{
		tbl[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	return (tbl);
}

int			ft_exec(t_data *data, char **args)
{
	pid_t			father;

	father = fork();
	if (father > 0)
	{
		wait(0);
	}
	if (father == 0)
	{
		execve(data->path, args, data->environ);
	}
	data->test++;
	return (0);
}


int			ft_search(char **args, t_data *data)
{
	char	**tbl_path;
	char	*path1;

	data->i = 0;
	data->test = 0;
	tbl_path = ft_strsplit(get_var_env(data, "PATH="), ':');
	while (tbl_path[data->i] && data->test == 0)
	{
		path1 = ft_strjoin(tbl_path[data->i], "/");
		data->path = ft_strjoin(path1, args[0]);
		ft_choice(args, data);
		data->i++;
	}
	free(tbl_path);
	return (0);
}

