/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:28:11 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/22 18:34:08 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal)
{
	(void)	signal;

	write(1, "signal received\n", 16);
	write(1, &message, 5);
	ft_printf("message int: %i\n", (int) message);
	message = 0;
}

int	main(void)
{
	pid_t	pid;
	struct sigaction	sa;
	sa.sa_handler = signal_handler;

	pid = getpid();
	ft_printf("%i\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	while (1)
	{
		pause();
	}

}
