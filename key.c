/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 02:43:27 by vcourtin          #+#    #+#             */
/*   Updated: 2014/02/06 02:43:34 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

char	*ascii_key(t_data *data, char *buff, char *stdin, int j)
{
	tputs(tgetstr("im", NULL), 1, ft_outc);
	delete_cmd(data, j);
	buff = add_to_tab(buff, stdin[0], j);
	ft_putstr_term(buff, data);
	back_to_j(buff, j);
	return (buff);
}

int		escape_key(t_data *data, char *buff, int j, char *stdin)
{
	if (stdin[1] == 91)
	{
		if (stdin[2] == 49)
			return ((j = ft_ctrl(data, buff, j)));
		else if (stdin[2] == 72)
			ft_putstr_fd("Home\n", 2);
		else if (stdin[2] == 70)
			ft_putstr_fd("End\n", 2);
		else
			return ((j = arrow_key(data, buff, j, stdin)));
	}

	if (stdin[1] == 0 && stdin[2] == 0)
	{
		reset_term(data);
		tputs(tgetstr("ei", NULL), 0, ft_outc);
		return (-1);
	}
	return (0);
}

int		arrow_key(t_data *data, char *buff, int j, char *stdin)
{
	if (stdin[2] == 65)
	{
		j = up_arrow(data, j, buff);
		ft_putstr_term(buff, data);
	}
	else if (stdin[2] == 66)
	{
		j = down_arrow(data, j, buff);
		ft_putstr_term(buff, data);
	}
	else if (stdin[2] == 68)
		j = left_arrow(j);
	else if (stdin[2] == 67)
		j = right_arrow(j, buff, data);
	return (j);
}

int		ft_mini_enter(t_data *data, char *buff)
{
	char	**test;
	int		i;

	i = 0;
	lseek(data->fd_history, 0, SEEK_END);
	if (ft_strcmp(buff, ""))
	{
		ft_putstr_fd(buff, data->fd_history);
		ft_putchar_fd('\n', data->fd_history);
	}
	ft_putchar('\n');
	test = ft_strsplit(buff, ';');
	while (test[i])
	{
		ft_parseur(test[i], data);
		i++;
	}
	return (0);
}

int		enter_key(t_data *data, char *buff)
{
	reset_term(data);
	lseek(data->fd_history, -1, SEEK_END);
	data->history_last = UP;
	if (buff[0] == '\0')
	{
		ft_putchar('\n');
		init_term(data);
		return (0);
	}
	ft_mini_enter(data, buff);
	init_term(data);
	return (0);
}

