/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 10:18:28 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/29 10:18:30 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

int		up_arrow(t_data *data, int j, char *buff)
{
	char	*cmd;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(buff);
	delete_cmd(data, len);
	j = 0;
	if (data->history_last == 1 && len)
		get_prev_line(data->fd_history, data);
	data->history_last = 2;
	if ((cmd = get_prev_line(data->fd_history, data)) == NULL)
		return (len);
	ft_strclr(buff);
	while (cmd[i] != '\0')
	{
		buff[j] = cmd[i];
		i++;
		j++;
	}
	buff[j] = '\0';
	return (j);
}

int		down_arrow(t_data *data, int j, char *buff)
{
	char	*cmd;
	int		i;

	i = 0;
	delete_cmd(data, j);
	j = 0;
	if (data->history_last == 2)
		get_next_line_m(data->fd_history);
	data->first_history = 0;
	data->history_last = 1;
	if ((cmd = get_next_line_m(data->fd_history)) == NULL)
		return (0);
	ft_strclr(buff);
	while (cmd[i] != '\0')
	{
		buff[j] = cmd[i];
		i++;
		j++;
	}
	buff[j] = '\0';
	return (j);
}

int		left_arrow(int j)
{
	if (j == 0)
		return (j);
	tputs(tgetstr("le", NULL), 1, ft_outc);
	return (j - 1);
}

int		right_arrow(int j, char *buff, t_data *data)
{
	char	*term_name;
	int		tmp;

	term_name = get_var_env(data,"TERM=");
	if (term_name == NULL)
		return (1);
	tgetent(NULL, term_name);
	if (j == (int)ft_strlen(buff))
		return (j);
	if ((j + ft_strlen(PROMPT)) % (tgetnum("co") - 1) == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_outc);
		tmp = tgetnum("co");
		while (tmp != 1)
		{
			tputs(tgetstr("le", NULL), 1, ft_outc);
			tmp--;
		}
	}
	else
		tputs(tgetstr("nd", NULL), 1, ft_outc);
	return (j + 1);
}
