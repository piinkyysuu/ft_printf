/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 05:21:39 by thule             #+#    #+#             */
/*   Updated: 2022/04/16 03:12:22 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void create_prefix_hashtag(t_proto *p, unsigned long long int n)
{
	if (n)
	{
		if (p->specifier == 'o')
			p->prefix = "0";
		else if (p->specifier == 'x')
			p->prefix = "0x";
		else if (p->specifier == 'X')
			p->prefix = "0X";
	}
	else
	{
		if (p->specifier == 'o' && !p->precision)
			p->prefix = "0";
	}
}

void unsigned_conversion_helper(t_proto *p, unsigned long long int n)
{
	int prefix_len;

	if (n || p->precision)
		p->number_len = number_len(n, p->base);
	if (p->hashtag)
		create_prefix_hashtag(p, n);
	prefix_len = ft_strlen(p->prefix);
	if (p->precision != -1)
		p->zero_padding = p->precision - p->number_len - prefix_len;
	else if (p->zero && !p->minus)
		p->zero_padding = p->width - p->number_len - prefix_len;
	if (p->zero_padding < 0)
		p->zero_padding = 0;
	p->counter = p->zero_padding + p->number_len + prefix_len;
	print_number_conversion(n, p);
}

void unsigned_conversion(t_proto *p, va_list *arg)
{
	if (ft_strcmp(p->length, "ll") == 0)
		unsigned_conversion_helper(p, (unsigned long long int)va_arg(*arg, unsigned long long int));
	else if (ft_strcmp(p->length, "hh") == 0)
		unsigned_conversion_helper(p, (unsigned char)va_arg(*arg, unsigned int));
	else if (ft_strcmp(p->length, "l") == 0)
		unsigned_conversion_helper(p, (unsigned long int)va_arg(*arg, unsigned long int));
	else if (ft_strcmp(p->length, "h") == 0)
		unsigned_conversion_helper(p, (unsigned short int)va_arg(*arg, unsigned int));
	else
		unsigned_conversion_helper(p, (unsigned int)va_arg(*arg, unsigned int));
}