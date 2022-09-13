/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:04:18 by thle              #+#    #+#             */
/*   Updated: 2022/04/21 18:48:31 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_float(t_float *f, t_proto *p, int reserved_len)
{
	int	xspace;
	int	prefix_len;

	xspace = 0;
	prefix_len = ft_strlen(p->prefix);
	reserved_len = reserved_len + prefix_len + p->zero_padding;
	if (p->width > reserved_len)
		xspace = p->width - reserved_len;
	if (!p->minus)
		padding_with_c(xspace, ' ');
	write(1, p->prefix, prefix_len);
	padding_with_c(p->zero_padding, '0');
	write(1, f->int_part, ft_strlen(f->int_part));
	if (f->exponent != 2047)
		write(1, f->frac_part, ft_strlen(f->frac_part));
	if (p->minus)
		padding_with_c(xspace, ' ');
	return (reserved_len + xspace);
}

void	initialize_float_struct(t_float *f, uint64_t format)
{
	f->sign = format >> 63;
	f->exponent = (format >> 52) & 2047;
	f->fraction = (format << 11) | (1UL << 63);
	f->int_part = NULL;
	f->frac_part = NULL;
}
