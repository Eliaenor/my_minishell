/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 04:58:39 by vcourtin          #+#    #+#             */
/*   Updated: 2014/02/09 04:58:43 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

int		ft_ctrl(t_data *data, char *buff, int j)
{
	char	stdin[3];

	read(1, &stdin, 3);
	if (stdin[0] == 59 && stdin[1] == 53)
	{
		if (stdin[2] == 67)
			j = goto_nextword(buff, j, data);
	}
	return (j);
}

int		goto_nextword(char *buff, int j, t_data *data)
{
	while (buff[j] != ' ' && buff[j] != '\0')
		j = right_arrow(j, buff, data);
	while (buff[j] == ' ' && buff[j] != '\0')
		j = right_arrow(j, buff, data);
	return (j);
}

