/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 03:53:49 by thule             #+#    #+#             */
/*   Updated: 2022/04/12 14:23:19 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	number_len(unsigned long long int n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

void	print_number(unsigned long long int n, int base, t_proto *p)
{
	char	c;
	int		remainder;

	if (n / base < 1)
		remainder = n % base;
	else
	{
		print_number(n / base, base, p);
		remainder = n % base;
	}
	c = remainder + '0';
	if (p->specifier == 'X' && remainder >= 10)
		c = remainder + '0' + 7;
	else if ((p->specifier == 'x' || p->specifier == 'p') && remainder >= 10)
		c = remainder + '0' + 39;
	write(1, &c, 1);
}

int		assign_base(t_proto *p)
{
	int	n;

	n = 16;
	if (p->specifier == 'o')
		n = 8;
	else if (p->specifier == 'u')
		n = 10;
	return (n);
}
