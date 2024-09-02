/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:18:03 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/02 17:43:36 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	main(void)
{
	unsigned int	pid;

	pid = getpid();
	if (pid < 0)
	{
		ft_putendl_fd("Failed to get PID", 2);
		exit(1);
	}
	ft_printf("Server PID: %u\n", pid);
	return (0);
}
