/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:27:54 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/05 19:28:03 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int sig);
static void	send_bits(pid_t pid, int var, int bits);
static void	setup_handler(void);

volatile sig_atomic_t	signal_received = 0;

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;
	int		len;

	if (argc != 3)
		print_error_and_exit(2);
	setup_handler();
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		print_error_and_exit(3);
	len = ft_strlen(argv[2]);
	if (len == 0)
		return (0);
	else if (len < 0)
		print_error_and_exit(6);
	else if (len > 2097152)
		print_error_and_exit(7);
	ft_printf("Len: %i\n", len);//REMOVE
	send_bits(pid, len, 24);
	i = 0;
	while (i < len)
	{
		send_bits(pid, (int) argv[2][i], 8);
		i++;
	}
	return (0);
}

static void	setup_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	if (sigemptyset(&sa.sa_mask) == -1 ||
		sigaction(SIGUSR1, &sa, NULL) == -1)
		print_error_and_exit(0);
}

static void	handler(int sig)
{
	(void) sig;

	signal_received = 1;
}

static void	send_bits(pid_t pid, int var, int bits)
{
	int	bit;
	int	result;
	int	time;

	ft_printf("Sending var=%i in %i bits\n", var, bits);
	bit = bits;
	while (bit > 0)
	{
		//ft_printf("signal was: %i\n", signal_received);//REMOVE
		signal_received = 0;
		//ft_printf("signal now: %i\n", signal_received);//REMOVE
		ft_printf("var: %i\n", var);
		if ((int) var % 2 == 0)
		{
			ft_printf("sending 0\n");//REMOVE
			result = kill(pid, SIGUSR1);
		}
		else
		{
			ft_printf("sending 1\n");//REMOVE
			result = kill(pid, SIGUSR2);
		}
		if (result == -1)
			print_error_and_exit(4);
		var >>= 1;
		bit--;
		time = 0;
		while (signal_received != 1)
		{
			time += SLEEP_TIME;
			usleep(SLEEP_TIME);
			if (time >= TIMEOUT)
				print_error_and_exit(8);
		}
	}
}
