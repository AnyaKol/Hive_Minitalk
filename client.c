/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:27:54 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/28 20:27:02 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_char_bits(pid_t pid, char c);

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;
	int		len;

	if (argc != 3)
		return (print_error(1));
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (print_error(2));
	i = 0;
	len = ft_strlen(argv[2]);
	ft_printf("Length: %i\n", len);
	while (i < len)
	{
		ft_printf("Letter: %c\n", argv[2][i]);
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
		usleep(200);
	}
	return (0);
}
