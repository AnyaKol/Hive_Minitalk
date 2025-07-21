/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:27:54 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/21 16:43:44 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	message = 0;

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		error;

	if (argc != 2)
		return (0);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (0);
	error = kill(pid, 1);
	if (error == 0)
		ft_printf("signal sent\n");
}
