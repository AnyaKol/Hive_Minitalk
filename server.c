/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:28:11 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/25 17:55:49 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putbinary(int c);

volatile sig_atomic_t	message = 0;

void	handler(int signal)
{
	message >>= 1;
	if (signal == SIGUSR2)
		message |= 128;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);//10
	sigaction(SIGUSR2, &sa, NULL);//12
	pid = getpid();
	ft_printf("%i\n", pid);
	while (1)
	{
	//	sigaddset(&block_mask, SIGUSR1);
	//	sigaddset(&block_mask, SIGUSR2);
		pause();
	//	sigemptyset(&block_mask);
		ft_printf("%c\n", (char) message);
		ft_putbinary((int) message);
		ft_printf("\n");
	}
	return (0);
}

void	ft_putbinary(int c)
{
	int		i;
	char	arr[8];

	i = 7;
	while (i >= 0)
	{
		if ((int) c % 2 == 0)
			arr[i] = '0';
		else
			arr[i] = '1';
		c >>= 1;
		i--;
	}
	write(1, arr, 8);
}
