/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:35:18 by thule             #+#    #+#             */
/*   Updated: 2022/04/12 14:48:18 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void padding_with_c(int len, char c)
{
	while (len)
	{
		write(1, &c, 1);
		len--;
	}
}

void field_width(t_proto *p)
{
	if (p->width > p->counter)
	{
		padding_with_c(p->width - p->counter, ' ');
		p->counter += p->width - p->counter;
	}
}

void printer_helper(t_proto *p)
{
	if (p->specifier == 'd' || p->specifier == 'i')
	{
		if (*(p->prefix))
			write(1, "-", 1);
		else if (p->plus)
			write(1, "+", 1);
		else if (p->space)
			write(1, " ", 1);
	}
	if (p->hashtag)
	{
		if (p->specifier == 'o' && p->precision < p->number_len)
			write(1, "0", 1);
		else if (p->specifier == 'x')
			write(1, "0x", 2);
		else if (p->specifier == 'X')
			write(1, "0X", 2);
	}
	if (p->precision > p->number_len)
		padding_with_c(p->precision - p->number_len, '0');
}

void	print_number_conversion(unsigned long long n, int base, t_proto *p)
{
	char c;

	c = ' ';
	if (p->zero)
		c = '0';
	if (p->width > p->counter)
	{
		if (!p->minus)
			padding_with_c(p->width - p->counter, c);
		printer_helper(p);
		print_number(n, base, p);
		if (p->minus)
			padding_with_c(p->width - p->counter, c);
		p->counter += p->width - p->counter;
	}
	else
	{
		printer_helper(p);
		print_number(n, base, p);
	}
}
