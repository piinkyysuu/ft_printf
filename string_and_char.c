/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_and_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:37:46 by thule             #+#    #+#             */
/*   Updated: 2022/04/12 14:51:39 by thle             ###   ########.fr       */
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
	write(1, &c, 1);
}

void	print_string(t_proto *p, va_list *arg)
{
	char	*s;
	int		strlen;

	s = (char *)va_arg(*arg, char *);
	if (!s)
	{
		s = "(null)";
		
	}
		





		
	strlen = ft_strlen(s);
	if ((p->precision != -1) && p->precision < strlen && ft_strcmp(s, "(null)"))
		strlen = p->precision;
	p->counter = strlen;
	if (!p->minus)
		field_width(p);
	write(1, s, strlen);
	if (p->minus)
		field_width(p);
}