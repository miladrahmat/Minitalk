/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:03:03 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/06 16:01:43 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	err_msg(unsigned int client_pid, char *err_msg, int err_flag)
{
	ft_putendl_fd(err_msg, 2);
	if (client_pid != 0)
		kill(client_pid, SIGUSR2);
	if (err_flag < 0)
		return (-1);
	else
		exit(1);
}

struct sigaction	define_sig_func(void *func)
{
	struct sigaction	new_signal;

	new_signal.sa_sigaction = func;
	new_signal.sa_flags = SA_SIGINFO;
	sigemptyset(&new_signal.sa_mask);
	return (new_signal);
}

void	check_final_status(int signal, siginfo_t *info, void *content)
{
	(void)content;
	(void)info;
	if (signal == SIGUSR1)
	{
		ft_printf("\e[1;32m Message sent successfully!\e[0m\n");
		exit(0);
	}
	else
		err_msg(0, "\e[1;31m Server error: Please restart server \e[0m", 1);
}

void	server_status_msg(int signal, siginfo_t *info, void *content)
{
	(void)info;
	(void)content;
	if (signal == SIGUSR2)
		err_msg(0, "\e[1;31m Server error: Please restart server \e[0m", 1);
}
