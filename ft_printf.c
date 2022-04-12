/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:41:36 by thule             #+#    #+#             */
/*   Updated: 2022/04/12 11:40:26 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	central_dispatch(t_proto *p, va_list *arg)
{
	char				*order;
	int					index;
	specifier_handler	*arr[12];

	index = 0;
	order = "cspdiouxXf%n";
	arr[f_c] = print_single_character;
	arr[f_percentage] = print_single_character;
	arr[f_s] = print_string;
	arr[f_d] = signed_conversion;
	arr[f_i] = signed_conversion;
	arr[f_u] = unsigned_conversion;
	arr[f_o] = unsigned_conversion;
	arr[f_x] = unsigned_conversion;
	arr[f_X] = unsigned_conversion;
	arr[f_p] = print_address;

	while (index < 12 && order[index] != p->specifier)
		index++;
	arr[index](p, arg);
}

int	ft_printf(const char *format, ...)
{
	va_list arg;
	t_proto p;
	int	counter;

	counter = 0;
	va_start(arg, format);
	prototype_initializer(&p);
	while (*format)
	{
		if (*format == '%')
		{
			// printf("before:%d ", p.counter);
			prototype_initializer(&p);
			prototype_handler(&format, &p);
			central_dispatch(&p, &arg);
			counter += p.counter;
			// printf("after:%d ", p.counter);
			// print_prototype(&p);
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
