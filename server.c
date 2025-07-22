/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:28:11 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/22 16:27:45 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal)
{
	(void)	signal;

	write(1, "Mrr~\n", 5);
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
