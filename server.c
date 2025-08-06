/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:28:11 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/06 12:11:44 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	setup_sigaction(void);
static void	handler(int sig, siginfo_t *info, void *ucontext);
static void	message_cicle(t_message *message);
static void	receive_len(t_message *message);
void	ft_putbinary(int c);

volatile sig_atomic_t	var = 0;

int	main(void)
{
	t_message	message;

	setup_sigaction();
	while (1)
	{
		receive_len(&message);
		message_cicle(&message);
		if (ft_printf("%s\n", message.str) == -1)
		{
			ft_free(message.str);
			print_error_and_exit(5);
		}
		ft_free(message.str);
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
		var |= 1 << 23;
	usleep(SLEEP_TIME);
	kill(info->si_pid, SIGUSR1);
}

static void	receive_len(t_message *message)
{
	int	bit_counter;
	//int len;

	bit_counter = 0;
	//len = 0;
	//ft_printf("Waiting...\n");
	while (bit_counter < 24)
	{
		/*
		if (bit_counter % 8 == 0)
		{
			len += var << (bit_counter / 8);
			ft_printf("len: %i\n", len);//REMOVE
			var = 0;
		}
		ft_printf("var: %i\n", var);//REMOVE
		ft_putbinary(var);//REMOVE
		*/
		pause();
		bit_counter++;
	}
	//ft_printf("var: %i\n", var);//REMOVE
	//ft_putbinary(var);//REMOVE
	message->len = var;
	message->str = ft_calloc(var + 1, sizeof(char));
	if (message->str == NULL)
		print_error_and_exit(1);
	//ft_printf("Len: %i\n", message->len);//REMOVE
}

static void	message_cicle(t_message *message)
{
	int		bit_counter;
	int		i;

	var = 0;
	bit_counter = 0;
	i = 0;
	while (1)
	{
		pause();
		bit_counter++;
		if (bit_counter == 8)
		{
			message->str[i] = var >> 16;
			i++;
			if (i == message->len)
				break ;
			bit_counter = 0;
		}
	}
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
	write(1, arr, 8);
	write(1, "\n", 1);
}
