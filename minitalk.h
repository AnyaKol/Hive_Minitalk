/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:29:08 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/05 16:33:03 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# ifndef SLEEP_TIME
#  define SLEEP_TIME 100
# endif
# ifndef TIMEOUT
#  define TIMEOUT 1000
# endif

#include "libft/libft.h"
#include <signal.h>
#include <sys/types.h>

typedef struct s_message
{
	char	*str;
	int		len;
}	t_message;

void	print_error_and_exit(int err_num);

#endif
