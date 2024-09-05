/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:03:03 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/05 19:18:10 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	err_msg(unsigned int client_pid, unsigned int client_pid1, char *err_msg)
{
	ft_putendl_fd(err_msg, 2);
	if (client_pid != 0)
		kill(client_pid, SIGUSR2);
	if (client_pid1 != 0)
		kill(client_pid1, SIGUSR2);
	return (-1);
}
