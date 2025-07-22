/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:27:54 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/22 16:25:32 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	message = 0;

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		result;

	if (argc != 2)
		return (0);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (0);
	result = kill(pid, SIGUSR1);
	if (result == 0)
		ft_printf("Meow~\n");
	else
		ft_printf("error\n");
}
