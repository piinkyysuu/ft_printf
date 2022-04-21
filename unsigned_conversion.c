/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 05:21:39 by thule             #+#    #+#             */
/*   Updated: 2022/04/20 00:37:35 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int unsigned_prefix(t_proto *p, unsigned long long int n, int nbr_len)
{
	if (n)
	{
		if (p->specifier == 'o' && p->precision < nbr_len)
			p->prefix = "0";
		else if (p->specifier == 'x')
			p->prefix = "0x";
		else if (p->specifier == 'X')
			p->prefix = "0X";
	}
	else
	{
		if (p->specifier == 'o' && !p->precision)
			p->prefix = "0";
	}
	return (ft_strlen(p->prefix));
}

int unsigned_conversion_helper(t_proto *p, unsigned long long int n)
{
	int prefix_len;
	int nbr_len;
	int	reserved_len;

	nbr_len = 0;
	prefix_len = 0;
	if (n || p->precision)
		nbr_len = number_len(n, p->base);
	if (p->hashtag)
		prefix_len = unsigned_prefix(p, n, nbr_len);
	reserved_len = zero_padding_value(p, nbr_len, prefix_len) + nbr_len + prefix_len;
	return print_number_conversion(n, p, reserved_len, prefix_len);
}

int unsigned_conversion(t_proto *p, va_list *arg)
{
	if (ft_strcmp(p->length, "ll") == 0)
		return unsigned_conversion_helper(p, (unsigned long long int)va_arg(*arg, unsigned long long int));
	else if (ft_strcmp(p->length, "hh") == 0)
		return unsigned_conversion_helper(p, (unsigned char)va_arg(*arg, unsigned int));
	else if (ft_strcmp(p->length, "l") == 0)
		return unsigned_conversion_helper(p, (unsigned long int)va_arg(*arg, unsigned long int));
	else if (ft_strcmp(p->length, "h") == 0)
		return unsigned_conversion_helper(p, (unsigned short int)va_arg(*arg, unsigned int));
	else
		return unsigned_conversion_helper(p, (unsigned int)va_arg(*arg, unsigned int));
	return (-1);
}