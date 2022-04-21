/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 03:53:49 by thule             #+#    #+#             */
/*   Updated: 2022/04/20 00:10:08 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int number_len(unsigned long long int n, int base)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

void print_number(unsigned long long int n, int base, t_proto *p)
{
	char c;
	int remainder;

	if (n / base < 1)
		remainder = n % base;
	else
	{
		print_number(n / base, base, p);
		remainder = n % base;
	}
	c = remainder + '0';
	if (p->specifier == 'X' && remainder >= 10)
		c = remainder + '0' + 7;
	else if ((p->specifier == 'x' || p->specifier == 'p') && remainder >= 10)
		c = remainder + '0' + 39;
	write(1, &c, 1);
}

int print_number_conversion(unsigned long long n, t_proto *p, int reserved_len, int prefix_len)
{
	int xspace;

	xspace = 0;
	if (p->width > reserved_len)
		xspace = p->width - reserved_len;
	if (!p->minus)
		padding_with_c(xspace, ' ');
	write(1, p->prefix, ft_strlen(p->prefix));
	if (p->precision || n)
	{
		padding_with_c(p->zero_padding, '0');
		print_number(n, p->base, p);
	}
	if (p->minus)
		padding_with_c(xspace, ' ');
	return (reserved_len + xspace);
}


int	zero_padding_value(t_proto *p, int nbr_len, int prefix_len)
{
	int zero_padding;

	zero_padding = 0;
	if (p->precision != -1)
		zero_padding = p->precision - nbr_len;
	else if (p->zero && !p->minus)
		zero_padding = p->width - nbr_len - prefix_len;
	zero_padding = ft_max(zero_padding, 0);
	p->zero_padding = zero_padding;
	return (zero_padding);
}