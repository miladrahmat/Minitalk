/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:05:38 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/09/04 15:06:05 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define _POSIX_C_SOURCE 199309L
# define _DEFAULT_SOURCE

# ifndef WAIT_TIME
#  define WAIT_TIME 500
# endif

# include "libft.h"
# include "vector.h"
# include <signal.h>

int	err_msg(unsigned int client_pid, unsigned int client_pid1, char *err_msg);

#endif