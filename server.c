/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:28:11 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/06 18:03:37 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	setup_sigaction(void);
static void	handler(int sig, siginfo_t *info, void *ucontext);
static void	message_cicle(t_message *message);
static void	receive_len(t_message *message);

volatile sig_atomic_t	g_var = 0;

int	main(void)
{
	setup_sigaction();
	while (1)
		pause();
	return (0);
}

static void	setup_sigaction(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigemptyset(&sa.sa_mask) == -1
		|| sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		print_error_and_exit(0);
	pid = getpid();
	if (pid <= 0)
		print_error_and_exit(3);
	if (ft_printf("%i\n", pid) == -1)
		print_error_and_exit(5);
}

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static t_message	message;

	(void) ucontext;
	g_var >>= 1;
	if (sig == SIGUSR2)
		g_var |= 1 << 23;
	if (message.len == 0)
		receive_len(&message);
	else
		message_cicle(&message);
	kill(info->si_pid, SIGUSR1);
}

static void	receive_len(t_message *message)
{
	message->bit_counter++;
	if (message->bit_counter != 24)
		return ;
	message->bit_counter = 0;
	message->len = g_var;
	message->str = ft_calloc(g_var + 1, sizeof(char));
	if (message->str == NULL)
		print_error_and_exit(1);
}

static void	message_cicle(t_message *message)
{
	message->bit_counter++;
	if (message->bit_counter != 8)
		return ;
	message->bit_counter = 0;
	message->str[message->index] = g_var >> 16;
	message->index++;
	if (message->index == message->len)
	{
		if (ft_printf("%s\n", message->str) == -1)
		{
			ft_free(message->str);
			print_error_and_exit(5);
		}
		ft_free(message->str);
		message->len = 0;
		message->index = 0;
	}
}
