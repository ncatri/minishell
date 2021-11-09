/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:25:10 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:25:12 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	replace_pwd(t_pwd_replace var)
{
	int		index;
	char	*pwd;
	char	buff[PATH_MAX];

	if (var == PWD)
		index = find_key_index(g_global.envp, "PWD");
	else
		index = find_key_index(g_global.envp, "OLDPWD");
	delete_key(index);
	getcwd(buff, PATH_MAX);
	if (var == PWD)
		pwd = ft_strjoin("PWD=", buff);
	else
		pwd = ft_strjoin("OLDPWD=", buff);
	pushback_env((void ***)&g_global.envp, ft_strdup(pwd), \
		number_of_split(g_global.envp));
	free(pwd);
	return (1);
}
