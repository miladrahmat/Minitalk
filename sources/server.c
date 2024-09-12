/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:18:03 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/12 19:29:31 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	check_sender(siginfo_t *info, volatile bool *process, \
	pid_t *client_pid)
{
	if (*process == true && *client_pid != info->si_pid)
	{
		usleep(50);
		if (kill(info->si_pid, SIGUSR2) < 0)
			return (err_msg(info->si_pid, \
				"\e[1;31m Signal sending failed \e[0m", -1));
		return (-2);
	}
	if (*process == false)
	{
		usleep(1000);
		if (kill(info->si_pid, SIGUSR1) < 0)
			return (err_msg(info->si_pid, \
				"\e[1;31m Signal sending failed \e[0m", -1));
		*client_pid = info->si_pid;
		*process = true;
		return (-2);
	}
	return (1);
}

static int	push_to_vector(pid_t client_pid, volatile bool *process, \
	t_vec *msg, char c)
{
	if (msg->memory == NULL)
		if (vec_new(msg, 1, sizeof(char)) < 0)
			return (err_msg(client_pid, \
				"\e[1;31m Malloc error \e[0m", -1));
	if (vec_push(msg, &c) < 0)
		return (err_msg(client_pid, \
			"\e[1;31m Malloc error \e[0m", -1));
	if (c == '\0')
	{
		if (ft_printf("%s\n", msg->memory) < 0)
			return (err_msg(client_pid, \
				"\e[1;31m ft_printf failed to output message \e[0m", -1));
		vec_free(msg);
		*process = false;
		usleep(500);
		if (kill(client_pid, SIGUSR1) < 0)
			return (err_msg(client_pid, \
				"\e[1;31m Signal sending failed \e[0m", -1));
	}
	return (1);
}

static int	process_msg(pid_t client_pid, int signal, \
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
	usleep(1);
	if (kill(client_pid, SIGUSR1) < 0)
		return (err_msg(client_pid, \
			"\e[1;31m Signal sending failed \e[0m", -1));
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
	static pid_t				client_pid;
	int							check;

	(void)content;
	check = check_sender(info, &processing_msg, &client_pid);
	if (check == -2)
		return ;
	else if (check == -1)
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
	pid_t				pid;

	pid = getpid();
	if (ft_printf("Server PID: %u\n", pid) < 0)
		return (err_msg(0, "\e[1;31m ft_printf failed to output PID \e[0m", 1));
	define_sig_func(&new_signal, &handle_signals);
	while (1)
		pause();
	return (0);
}
