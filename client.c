/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:27:54 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/06 17:41:01 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	setup_handler(void);
static void	handler(int sig);
static void	send_bits(pid_t pid, int var, int bits);

volatile sig_atomic_t	g_signal_received = 0;

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
	sa.sa_flags = SA_NODEFER;
	if (sigemptyset(&sa.sa_mask) == -1
		|| sigaction(SIGUSR1, &sa, NULL) == -1)
		print_error_and_exit(0);
}

static void	handler(int sig)
{
	(void) sig;
	g_signal_received = 1;
}

static void	send_bits(pid_t pid, int var, int bits)
{
	int	bit;
	int	result;
	int	time;

	bit = bits;
	while (bit > 0)
	{
		g_signal_received = 0;
		if ((int) var % 2 == 0)
			result = kill(pid, SIGUSR1);
		else
			result = kill(pid, SIGUSR2);
		if (result == -1)
			print_error_and_exit(4);
		var >>= 1;
		bit--;
		time = 0;
		while (g_signal_received != 1)
		{
			time += SLEEP_TIME;
			usleep(SLEEP_TIME);
			if (time >= TIMEOUT)
				print_error_and_exit(8);
		}
	}
}
