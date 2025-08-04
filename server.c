/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:28:11 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/04 17:59:04 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	setup_sigaction(void);
static void	handler(int sig, siginfo_t *info, void *ucontext);
static void	message_cicle();
static void	receive_len(char **message);
void	ft_putbinary(int c);

volatile sig_atomic_t	var = 0;

int	main(void)
{
	char	*message;

	setup_sigaction();
	while (1)
	{
		receive_len(&message);
		message_cicle(message);
		if (ft_printf("%s", message) == -1)
		{
			ft_free(message);
			print_error_and_exit(5);
		}
		free(message);
	}
	return (0);
}

static void	setup_sigaction(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigemptyset(&sa.sa_mask) == -1 ||
		sigaction(SIGUSR1, &sa, NULL) == -1 ||
		sigaction(SIGUSR2, &sa, NULL) == -1)
		print_error_and_exit(0);
	pid = getpid();
	if (pid <= 0)
		print_error_and_exit(3);
	if (ft_printf("%i\n", pid) == -1)
		print_error_and_exit(5);
}

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;

	var >>= 1;
	if (sig == SIGUSR2)
	{
		var |= 128;
		//ft_printf("received 1\n");
	}
	else
	{
		//ft_printf("received 0\n");
	}
	usleep(SLEEP_TIME);
	kill(info->si_pid, SIGUSR1);
}

static void	message_cicle()
{
	int		bit_counter;
	int		i;
	int		len;

	var = 0;
	bit_counter = 0;
	i = 0;
	while (1)
	{
		pause();
		bit_counter++;
		if (bit_counter == 8)
		{
			message[i] = var;
			i++;
			if (i == len)
				break ;
			bit_counter = 0;
		}
	}
}

static void	receive_len(char **message)
{
	int		bit_counter;

	bit_counter = 0;
	//ft_printf("Receiving len in 2 bytes\n");
	while (bit_counter < 8)
	{
		pause();
		ft_printf("var: %i\n", var);
		ft_putbinary(var);
		bit_counter++;
	}
	*message = ft_calloc(var + 1, sizeof(char));
	if (*message == NULL)
		print_error_and_exit(1);
	ft_printf("Len: %i\n", var);
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
	write(1, arr, 16);
	write(1, "\n", 1);
}
