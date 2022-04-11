/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 05:21:39 by thule             #+#    #+#             */
/*   Updated: 2022/04/10 05:22:06 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	case_0(t_proto *p)
{
	if ((!p->precision && p->specifier == 'o') || 
		p->precision && (p->specifier == 'u' || 
		p->specifier == 'x' || p->specifier == 'X'))
	{
		p->counter++;
		field_width(p);
		write(1, "0", 1);
		field_width(p);
		return ;
	}
	if (!p->precision)
	{
		field_width(p);
		return ;
	}
}

void	print_unsigned_conversion(t_proto *p, unsigned long long int n)
{
	int	base;

	base = assign_base(p);
	if (!n)
	{
		case_0(p);
		return;
	}
	p->number_len = number_len(n, base);
	if (p->precision > p->number_len)
		p->counter += p->precision;
	else
		p->counter += p->number_len;
	if (p->hashtag && p->specifier == 'o' && p->precision < p->number_len)
		p->counter++;
	if (p->hashtag && (p->specifier == 'x' || p->specifier == 'X'))
		p->counter = p->counter + 2;
	if (!p->minus)
		field_width(p);
	printer_helper(p);
	print_number(n, base, p);
	if (p->minus)
		field_width(p);
}

void	unsigned_conversion(t_proto *p, va_list *arg)
{
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