/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address_char_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:37:46 by thule             #+#    #+#             */
/*   Updated: 2022/04/16 03:29:56 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void print_address(t_proto *p, va_list *arg)
{
	unsigned long long n;
	int counter;

	counter = 0;
	n = va_arg(*arg, unsigned long long);
	p->number_len = number_len(n, p->base);
	p->counter = 2 + p->number_len;
	if (p->width > p->counter)
		counter = p->width - p->counter;
	if (!p->minus)
		padding_with_c(counter, ' ');
	write(1, "0x", 2);
	print_number(n, p->base, p);
	if (p->minus)
		padding_with_c(counter, ' ');
	p->counter += counter;
}

void print_character(t_proto *p, va_list *arg)
{
	char c;
	int counter;

	c = '%';
	counter = 0;
	if (p->specifier == 'c')
		c = (unsigned char)va_arg(*arg, int);
	p->counter = p->counter + 1;
	if (p->width > p->counter)
		counter = p->width - p->counter;
	if (!p->minus)
		padding_with_c(counter, ' ');
	write(1, &c, 1);
	if (p->minus)
		padding_with_c(counter, ' ');
	p->counter += counter;
}

void print_string(t_proto *p, va_list *arg)
{
	char *s;
	int counter;

	counter = 0;
	s = (char *)va_arg(*arg, char *);
	if (!s)
		s = "(null)";
	p->counter = ft_strlen(s);
	if ((p->precision != -1) && p->precision < p->counter)
		p->counter = p->precision;
	if (p->width > p->counter)
		counter = p->width - p->counter;
	if (!p->minus)
		padding_with_c(counter, ' ');
	write(1, s, p->counter);
	if (p->minus)
		padding_with_c(counter, ' ');
	p->counter += counter;
}
