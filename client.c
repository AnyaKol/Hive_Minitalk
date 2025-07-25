/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:27:54 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/25 18:34:46 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	print_error(void);
int	send_char_bits(pid_t pid, char c);

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		result;
	int		bytes_read;
	char	c;

	if (argc != 2)
		return (1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (1);
	while (1)
	{
		bytes_read = read(0, &c, 1);
		if (bytes_read < 0)
			return (1);
		if (bytes_read == 0)
			break ;
		if (c != '\0' && c != '\n')
		{
			result = send_char_bits(pid, c);
			if (result == -1)
				return (print_error());
		}
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
	}
	return (0);
}

int	print_error(void)
{
	ft_printf("error\n");
	return (1);
}
