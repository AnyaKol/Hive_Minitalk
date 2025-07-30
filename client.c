/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:27:54 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/30 20:00:33 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int sig);
static int	send_bits(pid_t pid, int var, int bits);
static int	setup_handler(void);

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;
	int		len;

	if (setup_handler() == -1)
		return (print_error(0));
	if (argc != 3)
		return (print_error(2));
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (print_error(3));
	i = 0;
	len = ft_strlen(argv[2]);
	if (len == 0)
		return (0);
	else if (len < 0)
		return (print_error(6));
	else if (len > 65535)
		return (print_error(7));
	ft_printf("Len: %i\n", len);
	if (send_bits(pid, len, 16) == -1)
		return (print_error(4));
	while (i < len)
	{
		if (send_bits(pid, (int) argv[2][i], 8) == -1)
			return (print_error(4));
		i++;
	}
	return (0);
}

static void	handler(int sig)
{
	(void) sig;
}

static int	send_bits(pid_t pid, int var, int bits)
{
	int	bit;
	int	result;

	ft_printf("Sending var=%i in %i bits\n", var, bits);
	bit = bits;
	while (bit > 0)
	{
		if ((int) var % 2 == 0)
		{
			//ft_printf("sending 0\n");
			result = kill(pid, SIGUSR1);
		}
		else
		{
			//ft_printf("sending 1\n");
			result = kill(pid, SIGUSR2);
		}
		if (result == -1)
			return (-1);
		var >>= 1;
		bit--;
		pause();
		usleep(SLEEP_TIME);
	}
	return (0);
}

static int	setup_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	if (sigemptyset(&sa.sa_mask) == -1 ||
		sigaction(SIGUSR1, &sa, NULL) == -1)
		return (-1);
	return (0);
}
