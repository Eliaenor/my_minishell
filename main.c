/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/23 03:50:54 by vcourtin          #+#    #+#             */
/*   Updated: 2013/12/23 03:50:56 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

int		main(int argc, char **argv, char **env)
{
	t_data	data;

	data.environ = ft_tabdup(env);
	init_term(&data);
	data.history_last = 0;
	data.first_history = 0;
	data.fd_history = open(".shhistory", O_RDWR | O_CREAT,
							S_IRWXU | S_IRWXO | S_IRWXG);
	ft_init_global(&data);
	if (argc > 1 && argv)
	{
		ft_putstr(argv[0]);
		ft_putstr(": command not found: ");
		ft_putendl(argv[1]);
	}
	while (1)
	{
		if (ft_get_entry(&data) == -1)
			exit(0);
	}
	return (0);
}

int		ft_test2(t_data *data, char *buff, int j, char *stdin)
{
	if (stdin[0] == 27)
	{
		if ((j = escape_key(data, buff, j, stdin)) == -1)
			return (-1);
	}
	else
	{
		lseek(data->fd_history, -1, SEEK_END);
		data->history_last = 0;
		enter_key(data, buff);
		return (-2);
	}
	return (j);
}

char	*ft_test3(t_data *data, char *buff, int *j, char *stdin)
{
	if ((stdin[0] >= 32 && stdin[0] < 127) && stdin[1] == 0)
	{
		data->history_last = 0;
		buff = ascii_key(data, buff, stdin, *j);
		(*j)++;
	}
	else if (stdin[0] == 127)
	{
		if (buff[0] != '\0' && *j != 0)
		{
			delete_cmd(data, *j);
			buff = ft_delete(*j, buff);
			ft_putstr_term(buff, data);
			back_to_j(buff, (*j) - 2);
			(*j)--;
		}
	}
	return (buff);
}

int		ft_test(t_data *data, char *buff, int j)
{
	char	stdin[3];

	while (read(1, &stdin, 3))
	{
		if ((stdin[0] >= 32))
			buff = ft_test3(data, buff, &j, stdin);
		else if (stdin[0] == 27 || stdin[0] == 10)
		{
			j = ft_test2(data, buff, j, stdin);
			if (j < 0)
				return (j);
		}
		ft_bzero(stdin, 3);
	}
	return (0);
}

int		ft_get_entry(t_data *data)
{
	char	*buff;
	int		j;

	j = 0;
	buff = (char *)malloc(sizeof(char) * 262145);
	buff[262144] = '\0';
	ft_bzero(buff, 262144);
	lseek(data->fd_history, -1, SEEK_END);
	data->line = 1;
	ft_putstr(PROMPT);
	if (ft_test(data, buff, j) == -1)
		return (-1);
	return (init_term(data));
}
