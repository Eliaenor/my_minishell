/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_buff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/31 20:00:54 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/31 20:00:59 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"


int		delete_cmd(t_data *data, int j)
{
	int		curent_line;
	char	*term_name;
	int		total_len;

	term_name = get_var_env(data,"TERM=");
	if (term_name == NULL)
		return (1);
	tgetent(NULL, term_name);
	total_len = ft_strlen(PROMPT) + j;
	curent_line = (total_len / (tgetnum("co") + 1)) + 1;
	ft_del_line(data, curent_line);
	while (j + ft_strlen(PROMPT) >= 1)
	{
		j--;
		tputs(tgetstr("le", NULL), 0, ft_outc);
	}
	return (j);
}

int		back_to_j(char *buff, int j)
{
	int		i;

	i = ft_strlen(buff) - j;
	while (i > 1)
	{
		tputs(tgetstr("le", NULL), 1, ft_outc);
		i--;
	}
	return (j);
}

int		ft_del_line(t_data *data, int curent_line)
{
	while (data->line > curent_line)
	{
		curent_line++;
		tputs(tgetstr("do", NULL), 0, ft_outc);
	}
	while (data->line != 0)
	{
		tputs(tgetstr("dl", NULL), 1, ft_outc);
		tputs(tgetstr("up", NULL), 0, ft_outc);
		data->line--;
	}
	tputs(tgetstr("do", NULL), 0, ft_outc);
	return (0);
}
