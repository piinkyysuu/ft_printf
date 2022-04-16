/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 03:55:16 by thule             #+#    #+#             */
/*   Updated: 2022/04/16 03:13:36 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void signed_conversion_helper(t_proto *p, long long int n)
{
	if (n < 0)
	{
		n = -n;
		p->prefix = "-";
	}
	else if (n > -1)
	{
		if (p->plus)
			p->prefix = "+";
		else if (p->space)
			p->prefix = " ";
	}
	if (n || p->precision)
		p->number_len = number_len(n, p->base);
	if (p->precision != -1)
		p->zero_padding = p->precision - p->number_len;
	else if (p->zero && !p->minus)
		p->zero_padding = p->width - p->number_len - ft_strlen(p->prefix);
	if (p->zero_padding < 0)
		p->zero_padding = 0;
	p->counter = p->zero_padding + p->number_len + ft_strlen(p->prefix);
	print_number_conversion(n, p);
}

void signed_conversion(t_proto *p, va_list *arg)
{
	if (ft_strcmp(p->length, "ll") == 0)
		signed_conversion_helper(p, (long long int)va_arg(*arg, long long int));
	else if (ft_strcmp(p->length, "hh") == 0)
		signed_conversion_helper(p, (signed char)va_arg(*arg, int));
	else if (ft_strcmp(p->length, "l") == 0)
		signed_conversion_helper(p, (long int)va_arg(*arg, long int));
	else if (ft_strcmp(p->length, "h") == 0)
		signed_conversion_helper(p, (short int)va_arg(*arg, int));
	else
		signed_conversion_helper(p, (int)va_arg(*arg, int));
}
