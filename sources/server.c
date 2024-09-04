/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:18:03 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/04 13:33:01 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	check_sender(siginfo_t *info, volatile bool *process, \
	unsigned int *client_pid)
{
	if (*process == true && *client_pid != (unsigned int)info->si_pid)
		return (err_msg(*client_pid, \
			"Received signals from multiple sources. Aborting.."));
	if (*process == false)
	{
		*client_pid = (unsigned int)info->si_pid;
		*process = true;
	}
	return (1);
}

static int	push_to_vector(unsigned int client_pid, volatile bool *process, \
	t_vec *msg, char c)
{
	if (msg->memory == NULL)
		if (vec_new(msg, 1, sizeof(char)) < 0)
			return (err_msg(client_pid, "Malloc error. Aborting.."));
	if (vec_push(msg, &c) < 0)
		return (err_msg(client_pid, "Malloc error. Aborting.."));
	if (c == '\0')
	{
		if (ft_printf("%s\n", msg->memory) < 0)
			return (err_msg(client_pid, "ft_printf failed. Aborting.."));
		vec_free(msg);
		*process = false;
		kill(client_pid, SIGUSR1);
	}
	return (1);
}

static int	process_msg(unsigned int client_pid, int signal, \
	volatile bool *process, t_vec *msg)
{
	static char	current;
	static int	bits;

	if (signal == SIGUSR1)
	{
		current = current << 1 | 1;
		bits++;
	}
	else if (signal == SIGUSR2)
	{
		current = current << 1;
		bits++;
	}
	if (bits == 8)
	{
		if (push_to_vector(client_pid, process, msg, current) < 0)
			return (-1);
		current = 0;
		bits = 0;
	}
	return (1);
}

static void	handle_signals(int signal, siginfo_t *info, void *content)
{
	static t_vec				msg;
	static volatile bool		processing_msg = false;
	static unsigned int			client_pid;

	(void)content;
	if (check_sender(info, &processing_msg, &client_pid) < 0)
	{
		if (msg.memory != NULL)
			vec_free(&msg);
		exit(1);
	}
	if (processing_msg == true)
	{
		if (process_msg(client_pid, signal, &processing_msg, &msg) < 0)
		{
			if (msg.memory != NULL)
				vec_free(&msg);
			exit(1);
		}
	}
}

int	main(void)
{
	struct sigaction	new_signal;
	unsigned int		pid;

	pid = getpid();
	if (ft_printf("Server PID: %u\n", pid) < 0)
		err_msg(0, "ft_printf failed. Aborting..");
	new_signal.sa_sigaction = &handle_signals;
	new_signal.sa_flags = SA_SIGINFO;
	sigemptyset(&new_signal.sa_mask);
	sigaction(SIGUSR1, &new_signal, NULL);
	sigaction(SIGUSR2, &new_signal, NULL);
	while (1)
		pause();
	return (0);
}
