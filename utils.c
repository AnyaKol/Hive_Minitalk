/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:29:08 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/05 16:30:40 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_error_and_exit(int err_num)
{
	int	print_error;

	const char	*errors[9] =
	{
		"Handler setup failed",//0
		"Allocation failed",//1
		"Invalid number of arguments",//2
		"Invalid PID",//3
		"Failed to send signal",//4
		"Printf error",//5
		"ft_strlen error",//6
		"Message too long. Maximum length is %{SIZE_MAX}",//7
		"Server not responding. Timeout."//8
	};
	if (err_num > 8 || err_num < 0)
		print_error = ft_printf("No such error\n");
	else
		print_error = ft_printf("%s\n", errors[err_num]);
	if (print_error == -1)
		write(2, "Printf error\n", 13);
	exit(1);
}
