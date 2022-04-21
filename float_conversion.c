/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 23:50:20 by thule             #+#    #+#             */
/*   Updated: 2022/04/21 15:04:39 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void print_bit(uint64_t num)
{
	int i = 63;
	while (i >= 0)
	{
		if (i == 51 || i == 62)
			printf(" ");
		if ((num >> i) & 1)
			printf("1");
		else
			printf("0");
		i--;
	}
	printf("\n");
}

void print_amount_of_bits(uint64_t num, int i)
{
	while (i >= 0)
	{
		if ((num >> i) & 1)
			printf("1");
		else
			printf("0");
		i--;
	}
	printf("\n");
}

void print_arr(uint8_t *arr, int amount)
{
	int index = 0;
	while (index < amount)
	{
		printf("%d", arr[index]);
		index++;
	}
	printf("\n\n");
}

int print_float(t_float *f, t_proto *p, int reserved_len)
{
	int xspace;
	int	prefix_len;
	int	frac_len;
	
	xspace = 0;
	prefix_len = ft_strlen(p->prefix);
	reserved_len = reserved_len + prefix_len + p->zero_padding;
	if (p->width > reserved_len)
		xspace = p->width - reserved_len;
	if (!p->minus)
		padding_with_c(xspace, ' ');
	write(1, p->prefix, prefix_len);
	padding_with_c(p->zero_padding, '0');
	write(1, f->int_part, ft_strlen(f->int_part));
	if (f->exponent != 2047)
	{
		frac_len = ft_strlen(f->frac_part);
		if (!frac_len && p->hashtag)
		{
			write(1, ".", 1);
			reserved_len++;
		}
		else
			write(1, f->frac_part, frac_len);
	}
	if (p->minus)
		padding_with_c(xspace, ' ');
	return (reserved_len + xspace);
}

void initialize_float_struct(t_float *f, uint64_t format)
{
	f->sign			=	format >> 63;
	f->exponent		=	(format >> 52) & 2047;
	f->fraction		=	(format << 11) | (1UL << 63);
	f->int_part		=	NULL;
	f->frac_part	=	NULL;
}

int special_cases(t_float *f, t_proto *p, uint64_t format)
{
	int reserved_len;

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


int	float_conversion_helper(t_proto *p, double n, t_float *f, uint64_t format)
{
	uint8_t		int_arr[39];
	int			reserved_len;
	
	reserved_len = 0;
	ft_memset(int_arr, 0, 39);
	f->frac_part = create_frac_part(f, p->precision);
	if (!f->frac_part)
		return (-1);
	create_int_part(f, int_arr);
	rounding(f, int_arr, p->precision);
	f->int_part = int_str(int_arr);
	if (!f->int_part)
	{
		ft_strdel(&f->int_part);
		return (-1);
	}
	float_prefix(f, p);
	reserved_len = ft_strlen(f->frac_part) + ft_strlen(f->int_part);
	p->zero_padding = zero_padding_value(p, reserved_len, ft_strlen(p->prefix));
	reserved_len = print_float(f, p, reserved_len);
	ft_strdel(&f->frac_part);
	ft_strdel(&f->int_part);
	return (reserved_len);
}

int float_conversion(t_proto *p, va_list *arg)
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
		return special_cases(&f, p, format);
	return float_conversion_helper(p, n, &f, format);
}