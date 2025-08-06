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
	const char	*errors[9] = {
		"Handler setup failed",
		"Allocation failed",
		"Invalid number of arguments",
		"Invalid PID",
		"Failed to send signal",
		"Printf error",
		"ft_strlen error",
		"Message too long. Maximum length is %{SIZE_MAX}",
		"Server not responding. Timeout."
	};

	if (err_num > 8 || err_num < 0)
		write(2, "No such error\n", 14);
	else
	{
		if (ft_printf("%s\n", errors[err_num]) == -1)
			write(2, "Printf error\n", 13);
	}
	exit(1);
}
