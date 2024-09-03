/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:39:04 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/03 18:00:12 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static void	handle_errors(int ac, char **av)
{
	int	i;

	if (ac != 3)
	{
		ft_putendl_fd("\e[1;31m Invalid number of arguments \e[0m", 2);
		exit(1);
	}
	i = 0;
	while (av[1][i] != '\0')
	{
		if (av[1][i] < '0' || av[1][i] > '9')
		{
			ft_putendl_fd("\e[1;31m Invalid PID \e[0m", 2);
			exit(1);
		}
		i++;
	}
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
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	int		pid;
	int		i;

	handle_errors(ac, av);
	pid = ft_atoi(av[1]);
	if (pid == 0)
	{
		ft_putendl_fd("\e[1;31m Invalid PID \e[0m", 2);
		exit(1);
	}
	i = 0;
	while (av[2][i] != '\0')
		send_message(pid, av[2][i++]);
	send_message(pid, av[2][i]);
	exit(0);
}
