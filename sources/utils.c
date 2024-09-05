/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:03:03 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/05 21:06:52 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	err_msg(unsigned int client_pid, unsigned int client_pid1, char *err_msg, \
	int err_flag)
{
	ft_putendl_fd(err_msg, 2);
	if (client_pid != 0)
		kill(client_pid, SIGUSR2);
	if (client_pid1 != 0)
		kill(client_pid1, SIGUSR2);
	if (err_flag < 0)
		return (-1);
	else
		exit(1);
}
