/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_frac_part.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:36:48 by thule             #+#    #+#             */
/*   Updated: 2022/04/21 17:51:36 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	calc_frac_part(uint64_t frac_bit, uint8_t *res, int to_shift)
{
	uint8_t	arr[1077];
	int		index;

	index = 63;
	ft_memset(arr, 0, sizeof(uint8_t) * 1077);
	arr[0] = 5;
	while (to_shift--)
		divide_by_2(arr, 1077);
	while (index >= 0)
	{
		if ((frac_bit >> index) & 1)
			add_array(arr, res, 1077);
		divide_by_2(arr, 1077);
		index--;
	}
}

char	*frac_str(uint8_t *res, int size)
{
	int		index;
	char	*str;

	index = 0;
	if (size == 0)
		size = 20;
	str = (char *) malloc(sizeof(char) * (size + 3));
	if (!str)
		return (0);
	str[0] = '.';
	while (index < size + 1 && index < 1077)
	{
		str[index + 1] = res[index] + 48;
		index++;
	}
	str[index + 1] = '\0';
	return (str);
}

char	*create_frac_part(t_float *f, int precision)
{
	uint8_t		res[1077];
	uint64_t	frac_bit;
	int			to_shift;

	ft_memset(res, 0, sizeof(uint8_t) * 1077);
	to_shift = (int)f->exponent - 1023;
	frac_bit = f->fraction;
	if (to_shift >= -1)
	{
		if (to_shift == 63)
			frac_bit = frac_bit << to_shift;
		else
			frac_bit = frac_bit << (to_shift + 1);
		to_shift = 0;
	}
	else
		to_shift = (to_shift * -1) - 1;
	calc_frac_part(frac_bit, res, to_shift);
	return (frac_str(res, precision));
}
