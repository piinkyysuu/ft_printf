/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 23:50:20 by thule             #+#    #+#             */
/*   Updated: 2022/05/05 16:00:29 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	float_special_cases(t_float *f, t_proto *p, uint64_t format)
{
	int	reserved_len;

	reserved_len = 0;
	if (format << 12 == 0)
	{
		float_prefix(f, p);
		f->int_part = "inf";
	}
	else
		f->int_part = "nan";
	reserved_len = ft_strlen(f->int_part);
	return (print_float(f, p, reserved_len));
}

int	float_other_cases(t_proto *p, t_float *f)
{
	uint8_t		int_arr[39];
	int			reserved_len;

	reserved_len = 0;
	ft_memset(int_arr, 0, sizeof(uint8_t) * 39);
	f->frac_part = create_frac_part(f, p->precision);
	if (!f->frac_part)
		exit(0);
	create_int_part(f, int_arr);
	rounding(f, int_arr, p->precision, p->hashtag);
	f->int_part = int_str(int_arr);
	if (!f->int_part)
	{
		ft_strdel(&f->int_part);
		exit(0);
	}
	float_prefix(f, p);
	reserved_len = ft_strlen(f->frac_part) + ft_strlen(f->int_part);
	p->zero_padding = zero_padding_value(p, reserved_len, ft_strlen(p->prefix));
	reserved_len = print_float(f, p, reserved_len);
	ft_strdel(&f->frac_part);
	ft_strdel(&f->int_part);
	return (reserved_len);
}

int	float_conversion(t_proto *p, va_list *arg)
{
	double		n;
	uint64_t	format;
	t_float		f;

	n = 0;
	if (p->precision < 0)
		p->precision = 6;
	if (!ft_strcmp(p->length, "L"))
		n = (double)va_arg(*arg, long double);
	else
		n = (double)va_arg(*arg, double);
	ft_memcpy(&format, &n, sizeof(uint64_t));
	initialize_float_struct(&f, format);
	if (f.exponent == 2047)
		return (float_special_cases(&f, p, format));
	return (float_other_cases(p, &f));
}
