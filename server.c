/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:28:11 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/30 20:07:27 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int sig, siginfo_t *info, void *ucontext);
static int	receive_len(char **message);
static int	setup_sigaction(void);
void	ft_putbinary(int c);

volatile sig_atomic_t	var = 0;

int	main(void)
{
	int		bit_counter;
	int		i;
	int		len;
	char	*message;

	if (setup_sigaction() == 1)
		return (1);
	len = receive_len(&message);
	if (len == -1)
		return (print_error(1));
	var = 0;
	bit_counter = 0;
	i = 0;
	while (1)
	{
		pause();
		bit_counter++;
		if (bit_counter == 8)
		{
			message[i] = var >> 8;
			i++;
			if (i == len)
				break ;
			bit_counter = 0;
		}
	}
	ft_printf("%s", message);
	free(message);
	return (0);
}

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;

	var >>= 1;
	if (sig == SIGUSR2)
	{
		var |= 32768;
		//ft_printf("received 1\n");
	}
	else
	{
		//ft_printf("received 0\n");
	}
	usleep(SLEEP_TIME);
	kill(info->si_pid, SIGUSR1);
}

static int	receive_len(char **message)
{
	int		bit_counter;

	bit_counter = 0;
	ft_printf("Receiving len in 2 bytes\n");
	while (bit_counter < 16)
	{
		pause();
		ft_printf("var: %i\n", var);
		ft_putbinary(var);
		bit_counter++;
	}
	*message = ft_calloc(var, sizeof(char));
	if (*message == NULL)
		return (-1);
	ft_printf("Len: %i\n", var);
	return (var);
}

static int	setup_sigaction(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigemptyset(&sa.sa_mask) == -1 ||
		sigaction(SIGUSR1, &sa, NULL) == -1 ||
		sigaction(SIGUSR2, &sa, NULL) == -1)
		return (print_error(0));
	pid = getpid();
	if (pid <= 0)
		return (print_error(3));
	if (ft_printf("%i\n", pid) == -1)
		return (print_error(5));
	return (0);
}

void	ft_putbinary(int c)
{
	int		i;
	char	arr[16];

	i = 15;
	while (i >= 0)
	{
		if ((int) c % 2 == 0)
			arr[i] = '0';
		else
			arr[i] = '1';
		c >>= 1;
		i--;
	}
	write(1, arr, 16);
	write(1, "\n", 1);
}
