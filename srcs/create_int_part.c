/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_int_part.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:39:57 by thule             #+#    #+#             */
/*   Updated: 2022/04/21 19:33:03 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	calc_int_part(uint64_t int_bit, uint8_t *res, int to_shift)
{
	uint8_t	arr[39];
	int		index;

	ft_memset(arr, 0, sizeof(uint8_t) * 39);
	arr[38] = 1;
	index = 0;
	if (to_shift <= 52)
		int_bit = int_bit >> (52 - to_shift);
	else if (to_shift > 52)
	{
		while (to_shift > 52)
		{
			mutiply_by_2(arr, 39);
			to_shift--;
		}
	}
	while (index < 53)
	{
		if (int_bit & (1L << index))
			add_array(arr, res, 39);
		mutiply_by_2(arr, 39);
		index++;
	}
}

char	*int_str(uint8_t *res)
{
	int		index;
	int		pos;
	char	*str;

	index = 0;
	pos = 0;
	while (index < 39 && !res[index])
		index++;
	if (index == 39)
		return (ft_strdup("0"));
	str = (char *) malloc(sizeof(char) * (39 - index + 1));
	if (str)
	{
		while (index < 39)
		{
			str[pos] = res[index] + 48;
			pos++;
			index++;
		}
		str[pos] = '\0';
	}
	return (str);
}

void	create_int_part(t_float *f, uint8_t *res)
{
	uint64_t	int_bit;
	int			to_shift;

	int_bit = f->fraction >> 11;
	to_shift = (int)f->exponent - 1023;
	if (to_shift < -1)
		return ;
	else
		calc_int_part(int_bit, res, to_shift);
}
