/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:29:08 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/29 20:17:27 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# ifndef SLEEP_TIME
#  define SLEEP_TIME 100
# endif

#include "libft/libft.h"
#include <signal.h>
#include <sys/types.h>

int	print_error(int err_num);

#endif
