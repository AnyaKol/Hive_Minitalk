/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:27:54 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/22 18:40:18 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		result;
	int		bytes_read;
	char	c;

	if (argc != 2)
		return (0);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (0);
	while (1)
	{
		ft_printf("message int: %i\n", (int) message);
		bytes_read = read(0, &c, 1);
		ft_printf("bytes read: %i\n", bytes_read);
		message = c;
		ft_printf("message: %c\n", message);
		result = kill(pid, SIGUSR1);
		if (result == -1)
			ft_printf("error\n");
	}
}
