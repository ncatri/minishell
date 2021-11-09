/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:27:06 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:27:08 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_error	syntax_error(char c)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	write(2, &c, 1);
	write(2, "\n", 1);
	return (FAIL);
}

t_error	error_message(char *message)
{
	ft_putstr_fd(message, 2);
	return (FAIL);
}
