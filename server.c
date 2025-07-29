/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:28:11 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/29 20:17:13 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//void	ft_putbinary(int c);
static int	setup_handler(void);
static void	handler(int sig, siginfo_t *info, void *ucontext);

volatile sig_atomic_t	message = 0;

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;

	message >>= 1;
	if (sig == SIGUSR2)
		message |= 128;
	usleep(SLEEP_TIME);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int	bit_counter;

	if (setup_handler() == -1)
		return (print_error(0));
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

static int	setup_handler(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);//10
	sigaction(SIGUSR2, &sa, NULL);//12
	pid = getpid();
	if (pid > 0)
		return (ft_printf("%i\n", pid));
	return (-1);
}
/*
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
*/
