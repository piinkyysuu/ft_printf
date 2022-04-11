/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 02:07:03 by thule             #+#    #+#             */
/*   Updated: 2022/04/09 21:31:51 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{	
	int		sign;
	long	acc;

	sign = 1;
	acc = 0;
	while (ft_isspace(*str))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			sign = -1;
		}
		str++;
	}
	while (ft_isdigit(*str) && *str)
	{
		acc = acc * 10 + (*str - 48);
		str++;
	}
	return (acc * sign);
}
