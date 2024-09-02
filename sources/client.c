/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:39:04 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/02 17:17:34 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

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

static void	send_len(int pid, size_t len)
{
	int	bits;

	bits = 0;
	while (bits < 32)
	{
		if (len & 0x01)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		len = len >> 1;
		bits++;
		usleep(100);
	}
}

static void	send_message(int pid, unsigned char c)
{
	int	bits;

	bits = 0;
	while (bits < 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c = c >> 1;
		bits++;
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	int		pid;
	int		i;
	size_t	len;

	handle_errors(ac, av);
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		ft_putendl_fd("\e[1;31m Invalid PID \e[0m", 2);
		exit(1);
	}
	len = ft_strlen(av[2]);
	send_len(pid, len);
	i = 0;
	while (av[2][i] != '\0')
		send_message(pid, av[2][i]);
	send_message(pid, av[2][i]);
	exit(0);
}
