/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 05:21:39 by thule             #+#    #+#             */
/*   Updated: 2022/04/12 16:16:45 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	case_0(t_proto *p)
{
	if (p->specifier == 'o')
	{
		p->counter++;
		if (p->width > p->counter && !p->minus)
			padding_with_c(p->width - p->counter, ' ');
		write(1, "0", 1);
		if (p->width > p->counter && p->minus)
			padding_with_c(p->width - p->counter, ' ');
	}
	else
	{
		if (p->width > p->counter)
			padding_with_c(p->width - p->counter, ' ');
	}
	if (p->width > p->counter)
		p->counter += p->width - p->counter;
}

void	print_unsigned_conversion(t_proto *p, unsigned long long int n)
{
	int	base;

	base = assign_base(p);
	if (!n && p->precision < 1)
		case_0(p);
	else
	{
		p->number_len = number_len(n, base);
		p->counter += ft_max(p->precision, p->number_len);
		if (p->hashtag && n)
		{
			if (p->specifier == 'o' && p->precision < p->number_len)
				p->counter++;
			else if (p->specifier == 'x' || p->specifier == 'X')
				p->counter += 2;
		}
		print_number_conversion(n, base, p);
	}
}


void	unsigned_conversion(t_proto *p, va_list *arg)
{
	if (p->precision == -1)
		p->precision = 1;
	if (ft_strcmp(p->length, "ll") == 0)
		print_unsigned_conversion(p, (unsigned long long int)va_arg(*arg, unsigned long long int));
	else if (ft_strcmp(p->length, "hh") == 0)
		print_unsigned_conversion(p, (unsigned char)va_arg(*arg, unsigned int));
	else if (ft_strcmp(p->length, "l") == 0)
		print_unsigned_conversion(p, (unsigned long int)va_arg(*arg, unsigned long int));
	else if (ft_strcmp(p->length, "h") == 0)
		print_unsigned_conversion(p, (unsigned short int)va_arg(*arg, unsigned int));
	else
		print_unsigned_conversion(p, (unsigned int)va_arg(*arg, unsigned int));
}