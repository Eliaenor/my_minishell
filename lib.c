/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 16:42:49 by vcourtin          #+#    #+#             */
/*   Updated: 2013/12/28 16:42:57 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell3.h"

char		**ft_split_once_part2(char **tbl, char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != c)
	{
		tbl[0][i] = str[i];
		i++;
	}
	tbl[0][i] = str[i];
	i++;
	tbl[0][i] = '\0';
	while (str[i] != '\0')
	{
		tbl[1][j] = str[i];
		i++;
		j++;
	}
	tbl[1][j] = '\0';
	tbl[2] = NULL;
	return (tbl);
}

char		**ft_split_once(char *str, char c)
{
	char	**tbl;
	int		i;
	int		j;

	i = 0;
	tbl = (char **)malloc(sizeof(char *) * 3);
	while (str[i] != c)
		i++;
	tbl[0] = (char*)malloc(sizeof(char) * (i));
	j = i;
	while (str[j] != '\0')
		j++;
	tbl[1] = (char*)malloc(sizeof(char) * (j - i + 1));
	tbl = ft_split_once_part2(tbl, str, c);
	return (tbl);
}

char		**ft_tabdup(char **tbl1)
{
	char	**tbl2;
	int		i;

	i = 0;
	while (tbl1[i])
		i++;
	tbl2 = (char **)malloc(sizeof(char*) * (i + 1));
	i = 0;
	while (tbl1[i])
	{
		tbl2[i] = ft_strdup(tbl1[i]);
		i++;
	}
	tbl2[i] = NULL;
	return (tbl2);
}

void		ft_free_env(char **tbl)
{
	int		i;

	i = 0;
	while (tbl[i])
	{
		free(tbl[i]);
		i++;
	}
	free(tbl[i]);
	free(tbl);
}

void		create_var_env(t_data *data, char *nameofvar)
{
	char	*part1;
	char	*part2;
	char	*tmp;
	char	*pwd;

	part1 = "PATH=/usr/local/bin:/usr/bin:/bin:";
	part2 = "/usr/sbin:/sbin:/opt/X11/bin:/usr/texbin";
	if (ft_strcmp(nameofvar, "PATH=") == 0)
	{
		tmp = ft_strjoin(part1, part2);
		set_var_env(data, tmp);
		free(tmp);
	}
	else if (ft_strcmp(nameofvar, "PWD=") == 0)
	{
		tmp = NULL;
		tmp = getcwd(tmp, 1024);
		pwd = ft_strjoin("PWD=", tmp);
		free(tmp);
		set_var_env(data, pwd);
		free(pwd);
	}
	else if (ft_strcmp(nameofvar, "HOME=") == 0)
		set_var_env(data, "HOME=/");
}
