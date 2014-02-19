/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/30 16:27:12 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/30 16:27:14 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

char	*add_to_tab(char *tbl, char c, int pos)
{
	int		i;
	char	tmp;
	char	tmp2;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(tbl) + 2));
	while (i < pos)
	{
		dest[i] = tbl[i];
		i++;
	}
	tmp = tbl[i];
	dest[i++] = c;
	while (tbl[i] != '\0')
	{
		tmp2 = tbl[i];
		dest[i] = tmp;
		tmp = tmp2;
		i++;
	}
	dest[i] = tmp;
	dest[i + 1] = '\0';
	return (dest);
}

char	*ft_delete(int j, char *buff)
{
	char	*new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	new = malloc(ft_strlen(buff));
	while (buff[k]!= '\0')
	{
		if (i == j - 1)
			k++;
		new[i++] = buff[k++];
	}
	new[i] = '\0';
	return (new);
}
