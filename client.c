/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:27:54 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/29 20:17:01 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_char_bits(pid_t pid, char c);

static void	handler(int sig)
{
	(void) sig;
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;
	int		len;
	struct sigaction	sa;

	if (argc != 3)
		return (print_error(1));
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (print_error(2));
	sa.sa_handler = handler;
	sigaction(SIGUSR1, &sa, NULL);
	i = 0;
	len = ft_strlen(argv[2]);
	while (i < len)
	{
		if (send_char_bits(pid, argv[2][i]) == -1)
			return (print_error(3));
		i++;
	}
	return (0);
}

int	send_char_bits(pid_t pid, char c)
{
	int	bit;
	int	result;

	bit = 8;
	while (bit > 0)
	{
		if ((int) c % 2 == 0)
			result = kill(pid, SIGUSR1);
		else
			result = kill(pid, SIGUSR2);
		if (result == -1)
			return (-1);
		c >>= 1;
		bit--;
		pause();
		usleep(SLEEP_TIME);
	}
	return (0);
}
