/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:39:04 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/05 21:06:29 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile bool	g_server_available = false;

static pid_t	handle_errors(int ac, char **av)
{
	int		i;
	int		pid;

	if (ac != 3)
		return (err_msg(0, 0, "\e[1;31m Invalid number of arguments \e[0m", -1));
	i = 0;
	while (av[1][i] != '\0')
	{
		if (av[1][i] < '0' || av[1][i] > '9')
			return (err_msg(0, 0, "\e[1;31m Invalid PID \e[0m", -1));
		i++;
	}
	pid = ft_atoi(av[1]);
	if (pid == 0)
		return (err_msg(0, 0, "\e[1;31m Invalid PID \e[0m", 1));
	while (g_server_available == false)
	{
		if (kill(pid, SIGUSR1) < 0)
			return (err_msg(0, 0, "\e[1;31m Signal sending failed \e[0m", 1));
		pause();
	}
	return (pid);
}

static void	send_message(int pid, unsigned char c)
{
	int	bits;

	bits = 7;
	while (bits >= 0)
	{
		if (c & (1 << bits))
		{
			if (kill(pid, SIGUSR1) < 0)
				err_msg(0, 0, "\e[1;31m Signal sending failed \e[0m", 1);
		}
		else
		{
			if (kill(pid, SIGUSR2) < 0)
				err_msg(0, 0, "\e[1;31m Signal sending failed \e[0m", 1);
		}
		bits--;
		pause();
		usleep(100);
	}
}

static void	check_server_status(int signal, siginfo_t *info, void *content)
{
	(void)content;
	(void)info;
	if (signal == SIGUSR2)
	{
		err_msg(0, 0, \
			"\e[1;33m Server is occupied, waiting for confirmation \e[0m", -1);
		sleep(10);
	}
	else
		g_server_available = true;
}

static void	check_final_status(int signal, siginfo_t *info, void *content)
{
	(void)content;
	(void)info;
	if (signal == SIGUSR1)
	{
		ft_printf("\e[1;32m Message sent successfully!\e[0m\n");
		exit(0);
	}
	else
		err_msg(0, 0, "\e[1;31m Error: Server closed unexpectedly \e[0m", 1);
}

int	main(int ac, char **av)
{
	struct sigaction	new_signal;
	pid_t				pid;
	int					i;

	new_signal.sa_sigaction = &check_server_status;
	new_signal.sa_flags = SA_SIGINFO;
	sigemptyset(&new_signal.sa_mask);
	sigaction(SIGUSR1, &new_signal, NULL);
	sigaction(SIGUSR2, &new_signal, NULL);
	pid = handle_errors(ac, av);
	if (pid <= 0)
		exit(1);
	i = 0;
	while (av[2][i] != '\0')
		send_message(pid, av[2][i++]);
	send_message(pid, av[2][i]);
	new_signal.sa_sigaction = &check_final_status;
	new_signal.sa_flags = SA_SIGINFO;
	sigemptyset(&new_signal.sa_mask);
	sigaction(SIGUSR1, &new_signal, NULL);
	sigaction(SIGUSR2, &new_signal, NULL);
	pause();
	exit(0);
}
