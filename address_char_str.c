/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address_char_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:37:46 by thule             #+#    #+#             */
/*   Updated: 2022/04/19 23:27:49 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int print_address(t_proto *p, va_list *arg)
{
	unsigned long long n;
	int	xspace;
	int	reserved_len;

	xspace = 0;
	reserved_len = 0;
	n = va_arg(*arg, unsigned long long);
	p->number_len = number_len(n, p->base);
	reserved_len = 2 + p->number_len;
	if (p->width > reserved_len)
		xspace = p->width - reserved_len;
	if (!p->minus)
		padding_with_c(xspace, ' ');
	write(1, "0x", 2);
	print_number(n, p->base, p);
	if (p->minus)
		padding_with_c(xspace, ' ');
	return (reserved_len + xspace);
}

int print_character(t_proto *p, va_list *arg)
{
	char c;
	int xspace;
	int reserved_len;

	c = '%';
	xspace = 0;
	reserved_len = 0;
	if (p->specifier == 'c')
		c = (unsigned char)va_arg(*arg, int);
	reserved_len = reserved_len + 1;
	if (p->width > reserved_len)
		xspace = p->width - reserved_len;
	if (!p->minus)
		padding_with_c(xspace, ' ');
	write(1, &c, 1);
	if (p->minus)
		padding_with_c(xspace, ' ');
	return (xspace + reserved_len);
}

int print_string(t_proto *p, va_list *arg)
{
	char *s;
	int	xspace;
	int	reserved_len;

	xspace = 0;
	reserved_len = 0;
	s = (char *)va_arg(*arg, char *);
	if (!s)
		s = "(null)";
	reserved_len = ft_strlen(s);
	if ((p->precision != -1) && p->precision < reserved_len)
		reserved_len = p->precision;
	if (p->width > reserved_len)
		xspace = p->width - reserved_len;
	if (!p->minus)
		padding_with_c(xspace, ' ');
	write(1, s, reserved_len);
	if (p->minus)
		padding_with_c(xspace, ' ');
	return (xspace + reserved_len);
}
