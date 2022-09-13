/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:41:57 by thle              #+#    #+#             */
/*   Updated: 2022/05/05 16:01:46 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	precision_0(uint8_t *int_arr, char *frac_str, char hashtag)
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
					break ;
				}
				index++;
			}
		}
	}
	else if (frac_str[1] > '5')
		integer_plus_1(int_arr);
	ft_bzero(frac_str, ft_strlen(frac_str));
	if (hashtag)
		frac_str[0] = '.';
}

static void	other_precision(char *frac_str, \
						uint8_t *int_arr, int precision)
{
	int	index;

	index = precision;
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

void	rounding(t_float *f, uint8_t *int_arr, int precision, char hashtag)
{
	char	*frac_str;

	frac_str = f->frac_part;
	if (!precision)
		precision_0(int_arr, frac_str, hashtag);
	else if (precision > 0)
		other_precision(frac_str, int_arr, precision);
}
