/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:41:36 by thule             #+#    #+#             */
/*   Updated: 2022/04/21 20:02:36 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	central_dispatch(t_proto *p, va_list *arg)
{
	char				*order;
	int					index;
	t_specifier_handler	*arr[12];

	index = 0;
	order = "cspdiouxXf%";
	arr[f_c] = print_character;
	arr[f_percentage] = print_character;
	arr[f_s] = print_string;
	arr[f_d] = signed_conversion;
	arr[f_i] = signed_conversion;
	arr[f_u] = unsigned_conversion;
	arr[f_o] = unsigned_conversion;
	arr[f_x] = unsigned_conversion;
	arr[f_X] = unsigned_conversion;
	arr[f_p] = print_address;
	arr[f_f] = float_conversion;
	while (index < 11 && order[index] != p->specifier)
		index++;
	if (index < 11)
		return (arr[index](p, arg));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	t_proto	p;
	int		counter;

	counter = 0;
	va_start(arg, format);
	while (*format)
	{
		if (*format == '%')
		{	
			prototype_initializer(&p);
			prototype_handler(&format, &p);
			counter += central_dispatch(&p, &arg);
		}
		else
		{
			write(1, format, 1);
			counter++;
		}
		format++;
	}
	va_end(arg);
	return (counter);
}
