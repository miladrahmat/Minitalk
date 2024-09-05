/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:05:38 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/05 20:54:46 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "libft.h"
# include "vector.h"
# include <signal.h>

int	err_msg(unsigned int client_pid, unsigned int client_pid1, char *err_msg, \
	int err_flag);

#endif