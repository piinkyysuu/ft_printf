/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_and_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:37:46 by thule             #+#    #+#             */
/*   Updated: 2022/04/10 02:38:06 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_single_character(t_proto *p, va_list *arg)
{
	char	c;
	
	if (p->specifier == 'c')
		c = (unsigned char)va_arg(*arg, int);
	else if (p->specifier == '%')
		c = '%';
	p->counter = p->counter + 1;
	if (!p->minus)
		field_width(p);
	write(1, &c, 1);
	if (p->minus)
		field_width(p);
}

void	print_string(t_proto *p, va_list *arg)
{
	char	*s;
	int		strlen;

	s = (char *)va_arg(*arg, char *);
	if (!s)
		s = "(null)";
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