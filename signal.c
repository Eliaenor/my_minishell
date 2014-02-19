/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/27 18:05:58 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/27 18:06:00 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

t_data		*data_signal;

int			ft_init_global(t_data *data)
{
	data_signal = data;
	return (0);
}

void		sig_ctrl_c(int n)
{
	(void)n;
	signal(2, sig_ctrl_c);
	signal(3, sig_ctrl_c);
	ft_putchar('\n');
	ft_get_entry(data_signal);
}
