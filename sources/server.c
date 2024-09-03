/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:18:03 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/03 17:59:00 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

t_vec	msg;

static void	handle_signals(int signal, siginfo_t *info, void *content)
{
	static char		current;
	static int		bits;

	(void)info;
	(void)content;
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
		if (msg.memory == NULL)
			vec_new(&msg, 1, sizeof(char));
		vec_push(&msg, &current);
		if (current == '\0')
		{
			ft_printf("%s\n", msg.memory);
			vec_free(&msg);
		}
		current = 0;
		bits = 0;
	}
}

int	main(void)
{
	struct sigaction	new_signal;
	unsigned int		pid;

	pid = getpid();
	ft_printf("Server PID: %u\n", pid);
	new_signal.sa_sigaction = &handle_signals;
	new_signal.sa_flags = SA_SIGINFO;
	sigemptyset(&new_signal.sa_mask);
	sigaction(SIGUSR1, &new_signal, NULL);
	sigaction(SIGUSR2, &new_signal, NULL);
	while (1)
		pause();
	vec_free(&msg);
	return (0);
}
