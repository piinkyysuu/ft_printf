/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:41:57 by thle              #+#    #+#             */
/*   Updated: 2022/04/21 14:42:28 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	precision_0(uint8_t *int_arr, char *frac_str)
{
	int	index;

	index = 2;
	if (frac_str[1] == '5')
	{
		if (int_arr[38] % 2 != 0)
			integer_plus_1(int_arr);
		else
		{
			while (frac_str[index])
			{
				if (frac_str[index] != '0')
				{
					integer_plus_1(int_arr);
					break;
				}
				index++;
			}
		}
	}
	else if (frac_str[1] > '5')
		integer_plus_1(int_arr);
	ft_bzero(frac_str, ft_strlen(frac_str));
}

void	rounding(t_float *f, uint8_t *int_arr, int precision)
{
	char	*frac_str;
	int		index;

	index = precision;
	frac_str = f->frac_part;
	if (!precision)
		precision_0(int_arr, frac_str);
	else if (precision > 0)
	{
		if (frac_str[index + 1] >= '5')
		{
			if (frac_str[index] < '9')
				frac_str[index]++;
			else if (frac_str[index] == '9')
			{
				while (frac_str[index] == '9')
				{
					frac_str[index] = '0';
					index--;
				}
				if (ft_isdigit(frac_str[index]))
					frac_str[index]++;
				else
					integer_plus_1(int_arr);
			}
		}
		ft_bzero(frac_str + precision + 1, 1);
	}
}