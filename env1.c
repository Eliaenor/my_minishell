/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 20:40:34 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/13 20:40:36 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

char		*get_var_env(t_data *data, char *varenv)
{
	int		len;
	int		i;
	char	*str;

	i = 0;
	len = ft_strlen(varenv);
	while (data->environ[i] && ft_strncmp(data->environ[i], varenv, len) != 0)
		i++;
	str = data->environ[i];
	if (str != NULL)
		return (str + len);
	else
	{
		create_var_env(data, varenv);
		str = data->environ[i];
		return (str + len);
	}
}

char		**ft_addto_env(t_data *data, char *newvar)
{
	char	**newenv;
	int		i;

	i = 0;
	while (data->environ[i])
		i++;
	newenv = (char **)malloc(sizeof(char*) * (i + 2));
	i = 0;
	while (data->environ[i])
	{
		newenv[i] = ft_strdup(data->environ[i]);
		i++;
	}
	newenv[i] = ft_strdup(newvar);
	newenv[++i] = NULL;
	ft_free_env(data->environ);
	data->environ = newenv;
	return (newenv);
}

int			set_var_env(t_data *data, char *varenv)
{
	int		len;
	int		lenofvar;
	int		i;
	char	**tbl;

	i = 0;
	tbl = ft_split_once(varenv, '=');
	len = ft_strlen(tbl[0]);
	while (data->environ[i] && ft_strncmp(data->environ[i], tbl[0], len) != 0)
		i++;
	lenofvar = ft_strlen(tbl[1]);
	if (data->environ[i])
	{
		free(data->environ[i]);
		data->environ[i] = ft_strjoin(tbl[0], tbl[1]);
	}
	else
		ft_addto_env(data, ft_strjoin(tbl[0], tbl[1]));
	return (0);
}

int			ft_delto_env(t_data *data, char *nameofvar)
{
	char	**newenv;
	int		i;
	int		len;
	int		exist;

	i = 0;
	exist = 0;
	len = ft_strlen(nameofvar);
	while (data->environ[i])
	{
		if (ft_strncmp(data->environ[i], nameofvar, len) == 0)
			exist = 1;
		i++;
	}
	if (exist == 1)
		newenv = (char **)malloc(sizeof(char*) * (i));
	else
		return (-1);
	delto_env_part2(data, nameofvar, len, &newenv);
	ft_free_env(data->environ);
	data->environ = newenv;
	data->test++;
	return (0);
}

int		delto_env_part2(t_data *data, char *name, int len, char ***newenv)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->environ[i])
	{
		if (ft_strncmp(data->environ[i], name, len) == 0)
			i++;
		else
		{
			(*newenv)[j] = ft_strdup(data->environ[i]);
			j++;
			i++;
		}
	}
	(*newenv)[j] = NULL;
	return (0);
}
