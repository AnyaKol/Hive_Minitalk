/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:28:30 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/07 17:08:26 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (nptr[i] == '-')
	{
		sign = -sign;
		i++;
	}
	if (!ft_isdigit(nptr[i]))
			return (0);
	while (ft_isdigit(nptr[i]))
	{
		result = result * 10 + (nptr[i] - '0');
		if ((result > INT_MAX && sign == 1) || (-result) < INT_MIN)
			return (0);
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	result = result * sign;
	return (result);
}
