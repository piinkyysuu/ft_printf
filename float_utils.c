/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:44:03 by thule             #+#    #+#             */
/*   Updated: 2022/04/21 15:04:35 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void divide_by_2(uint8_t *arr, int len)
{
	int remainder;
	int index;
	int last_value;

	remainder = 0;
	index = 0;
	last_value = 0;
	while (index < len)
	{
		last_value = arr[index];
		arr[index] = ((remainder * 10) + arr[index]) / 2;
		if (last_value % 2 == 0)
			remainder = 0;
		else
			remainder = 1;
		index++;
	}
}

void	mutiply_by_2(uint8_t *arr, int len)
{
	int	plus_1;

	plus_1 = 0;
	len = len - 1;
	while (len >= 0)
	{
		arr[len] = (arr[len] * 2) + plus_1;
		if (arr[len] >= 10)
		{
			arr[len] = arr[len] - 10;
			plus_1 = 1;
		}
		else
			plus_1 = 0;
		len--;
	}
}

void	integer_plus_1(u_int8_t *int_arr)
{
	uint8_t one[39];

	ft_memset(one, 0, 39);
	one[38] = 1;
	add_array(one, int_arr, 39);
}

void add_array(uint8_t *arr, uint8_t *res, int len)
{
	len = len - 1;
	while (len >= 0)
	{
		res[len] = res[len] + arr[len];
		if (res[len] >= 10 && len != 0)
		{
			res[len - 1]++;
			res[len] -= 10;
		}
		len--;
	}
}

int float_prefix(t_float *f, t_proto *p)
{
	if (f->sign)
		p->prefix = "-";
	else
	{
		if (p->plus)
			p->prefix = "+";
		else if (p->space)
			p->prefix = " ";
	}
	return (ft_strlen(p->prefix));
}