/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_and_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:37:46 by thule             #+#    #+#             */
/*   Updated: 2022/04/12 15:05:30 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_single_character(t_proto *p, va_list *arg)
{
	char	c;
	
	c = '%';
	if (p->specifier == 'c')
		c = (unsigned char)va_arg(*arg, int);
	p->counter = p->counter + 1;
	if (p->width > p->counter)
	{
		if (!p->minus)
			padding_with_c(p->width - p->counter, ' ');
		write(1, &c, 1);
		if (p->minus)
			padding_with_c(p->width - p->counter, ' ');
		p->counter += p->width - p->counter;
	}
	else
		write(1, &c, 1);
}

void	print_string(t_proto *p, va_list *arg)
{
	char	*s;

	s = (char *)va_arg(*arg, char *);
	if (!s)
	{
		s = "(null)";
		p->counter = 6;
	}
	else
	{
		p->counter = ft_strlen(s);
		if ((p->precision != -1) && p->precision < p->counter)
			p->counter = p->precision;
	}
	if (p->width > p->counter)
	{
		if (!p->minus)
			padding_with_c(p->width - p->counter, ' ');
		write(1, s, p->counter);
		if (p->minus)
			padding_with_c(p->width - p->counter, ' ');
		p->counter += p->width - p->counter;
	}
	else
		write(1, s, p->counter);
}