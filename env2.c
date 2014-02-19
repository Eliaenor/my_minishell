/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 20:41:06 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/13 20:41:09 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

int			ft_setenv(t_data *data, char *varname, char *var)
{
	char	*varandname;
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(varname);
	tmp = ft_strjoin(varname, "=");
	varandname = ft_strjoin(tmp, var);
	set_var_env(data, varandname);
	free(varandname);
	data->test++;
	return (0);
}

int			ft_aff_env(t_data *data)
{
	int		i;

	i = 0;
	while (data->environ[i])
	{
		ft_putendl(data->environ[i]);
		i++;
	}
	data->test++;
	return (0);
}
