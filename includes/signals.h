/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:24:52 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:24:54 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <termios.h>
# include "minishell.h"

void	setup_terminal(void);
void	setup_main_signals(void);
void	handler(int signal);
void	process(int signal);
void	new_prompt(char c, int fd);

#endif
