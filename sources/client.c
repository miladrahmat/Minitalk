/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:39:04 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/04 13:43:20 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	handle_errors(int ac, char **av)
{
	int	i;

	if (ac != 3)
		return (err_msg(0, "\e[1;31m Invalid number of arguments \e[0m"));
	i = 0;
	while (av[1][i] != '\0')
	{
		if (av[1][i] < '0' || av[1][i] > '9')
			return (err_msg(0, "\e[1;31m Invalid PID \e[0m"));
		i++;
	}
	return (1);
}

static void	send_message(int pid, unsigned char c)
{
	int	bits;

	bits = 7;
	while (bits >= 0)
	{
		if (c & (1 << bits))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bits--;
		usleep(WAIT_TIME);
	}
}

static void	check_server_status(int signal, siginfo_t *info, void *content)
{
	(void)content;
	(void)info;
	if (signal == SIGUSR1)
	{
		ft_printf("Message sent!\n");
		exit(0);
	}
	else
	{
		ft_putendl_fd("Error: Server closed unexpectedly", 2);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	struct sigaction	new_signal;
	int					pid;
	int					i;

	if (handle_errors(ac, av) < 0)
		exit(1);
	pid = ft_atoi(av[1]);
	if (pid == 0)
	{
		err_msg(0, "\e[1;31m Invalid PID \e[0m");
		exit(1);
	}
	new_signal.sa_sigaction = &check_server_status;
	new_signal.sa_flags = SA_SIGINFO;
	sigemptyset(&new_signal.sa_mask);
	sigaction(SIGUSR1, &new_signal, NULL);
	sigaction(SIGUSR2, &new_signal, NULL);
	i = 0;
	while (av[2][i] != '\0')
		send_message(pid, av[2][i++]);
	send_message(pid, av[2][i]);
	while (1)
		pause();
	exit(0);
}
