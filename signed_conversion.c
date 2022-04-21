/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 03:55:16 by thule             #+#    #+#             */
/*   Updated: 2022/04/20 01:09:28 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	signed_prefix(t_proto *p, long long int n)
{
	if (n < 0 || p->plus || p-> space)
	{
		if (n < 0)
			p->prefix = "-";
		else if (p->plus)
			p->prefix = "+";
		else if (p->space)
			p->prefix = " ";
		return (1);
	}
	return (0);
}


int signed_conversion_helper(t_proto *p, long long int n)
{
	int	prefix_len;
	int	nbr_len;
	int	reserved_len;

	nbr_len = 0;
	reserved_len = 0;
	prefix_len = signed_prefix(p, n);
	if (n < 0)
		n = -n;
	if (n || p->precision)
		nbr_len = number_len(n, p->base);
	reserved_len = zero_padding_value(p, nbr_len, prefix_len) + nbr_len + prefix_len;
	return print_number_conversion(n, p, reserved_len, prefix_len);
}

int signed_conversion(t_proto *p, va_list *arg)
{
	if (ft_strcmp(p->length, "ll") == 0)
		return signed_conversion_helper(p, (long long int)va_arg(*arg, long long int));
	else if (ft_strcmp(p->length, "hh") == 0)
		return signed_conversion_helper(p, (signed char)va_arg(*arg, int));
	else if (ft_strcmp(p->length, "l") == 0)
		return signed_conversion_helper(p, (long int)va_arg(*arg, long int));
	else if (ft_strcmp(p->length, "h") == 0)
		return signed_conversion_helper(p, (short int)va_arg(*arg, int));
	else
		return signed_conversion_helper(p, (int)va_arg(*arg, int));
	return (-1);
}
