/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/27 17:40:13 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/27 17:40:17 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

int			init_term(t_data *data)
{
	char				*term_name;
	struct termios		term;

	term_name = get_var_env(data,"TERM=");
	if (term_name == NULL)
		return (1);
	tgetent(NULL, term_name);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_oflag &= ~(OPOST);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	return (0);
}

int			ft_outc(int c)
{
	write(isatty(1), &c, 1);
	return (0);
}

int			ft_putstr_term(char *str, t_data *data)
{
	int		i;
	int		char_to_print;
	char	*term_name;

	i = 0;
	term_name = get_var_env(data,"TERM=");
	if (term_name == NULL)
		return (1);
	tgetent(NULL, term_name);
	char_to_print = ft_strlen(PROMPT) + ft_strlen(str);
	data->line = (char_to_print / (tgetnum("co") + 1)) + 1;
	ft_putstr_fd(PROMPT, isatty(1));
	ft_putstr_fd(str, isatty(1));
	return (char_to_print);
}

int			reset_term(t_data *data)
{
	char				*term_name;
	struct termios		term;

	term_name = get_var_env(data,"TERM=");
	if (term_name == NULL)
		return (1);
	tgetent(NULL, term_name);
	tcgetattr(0, &term);
	term.c_lflag |= (ICANON | ECHO);
	term.c_oflag |= (OPOST);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	return (0);
}
