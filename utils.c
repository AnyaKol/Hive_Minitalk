/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:29:08 by akolupae          #+#    #+#             */
/*   Updated: 2025/07/29 20:10:44 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	print_error(int err_num)
{
	const char	*errors[4] =
	{
		"Handler setup failed",
		"Invalid number of arguments",
		"Invalid PID",
		"Failed to send signal"
	};
	if (err_num > 3)
		ft_printf("No such error\n");
	else
		ft_printf("%s\n", errors[err_num]);
	return (1);
}
