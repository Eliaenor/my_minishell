/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 00:02:25 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/14 00:02:27 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

void		ft_put_double_tab(char **tbl)
{
	int		i;

	i = 0;
	while (tbl[i])
	{
		ft_putendl(tbl[i]);
		i++;
	}
	ft_putchar('\n');
}

int			ft_parseur(char *str, t_data *data)
{
	char	**tbl;
	char	**args;
	int		i;

	i = 0;
	tbl = ft_strsplit(str, '|');
	while (tbl[i + 1])
		i++;
	data->nbrofpipes = i;
	i = 0;
	while (tbl[i])
	{
		args = ft_strsplit(tbl[i], ' ');
		ft_search(args, data);
		if (data->test == 0)
		{
			ft_putstr("minishell1: command not found: ");
			ft_putendl(args[0]);
		}
		data->test = 0;
		i++;
	}
	return (0);
}
