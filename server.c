/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:28:11 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/28 17:07:30 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putbinary(int c);

volatile sig_atomic_t	message = 0;

void	handler(int signal)
{
	//ft_printf("Received signal!\n");
	message >>= 1;
	if (signal == SIGUSR2)
		message |= 128;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;
	int					bit_counter;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);//10
	sigaction(SIGUSR2, &sa, NULL);//12
	pid = getpid();
	ft_printf("%i\n", pid);
	bit_counter = 0;
	while (1)
	{
		pause();
		bit_counter++;
		if (bit_counter == 8)
		{
			ft_printf("%c", (char) message);
			//ft_putbinary((int) message);
			//ft_printf("\n");
			bit_counter = 0;
		}
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
