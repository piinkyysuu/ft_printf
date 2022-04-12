/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 03:55:16 by thule             #+#    #+#             */
/*   Updated: 2022/04/12 15:23:50 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_signed_conversion(t_proto *p, long long int n)
{
	if (!p->precision && !n)
	{
		field_width(p);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		p->prefix = "-";
		p->counter++;
	}
	p->number_len = number_len(n, 10);
	p->counter += ft_max(p->precision, p->number_len);
	p->counter += (!(*p->prefix) && (p->plus || p->space));
	print_number_conversion(n, 10, p);
}

void	signed_conversion(t_proto *p, va_list *arg)
{
	if (ft_strcmp(p->length, "ll") == 0)
		print_signed_conversion(p, (long long int)va_arg(*arg, long long int));
	else if (ft_strcmp(p->length, "hh") == 0)
		print_signed_conversion(p, (signed char)va_arg(*arg, int));
	else if (ft_strcmp(p->length, "l") == 0)
		print_signed_conversion(p, (long int)va_arg(*arg, long int));
	else if (ft_strcmp(p->length, "h") == 0)
		print_signed_conversion(p, (short int)va_arg(*arg, int));
	else
		print_signed_conversion(p, (int)va_arg(*arg, int));
}
