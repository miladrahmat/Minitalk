/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:05:38 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/07 14:24:10 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "libft.h"
# include "vector.h"
# include <signal.h>

int		err_msg(unsigned int client_pid, char *err_msg, int err_flag);
void	define_sig_func(struct sigaction *new_signal, void *func);
void	check_final_status(int signal, siginfo_t *info, void *content);
void	server_status_msg(int signal, siginfo_t *info, void *content);

#endif