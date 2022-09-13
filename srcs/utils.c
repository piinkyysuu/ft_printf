/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:44:04 by thle              #+#    #+#             */
/*   Updated: 2022/04/21 19:49:34 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	assign_base(char c)
{
	int	base;

	base = 0;
	if (c == 'd' || c == 'i' || c == 'u')
		base = 10;
	else if (c == 'x' || c == 'X' || c == 'p')
		base = 16;
	else if (c == 'o')
		base = 8;
	return (base);
}

void	skip_space(const char **format)
{
	while (**format == ' ' && **format != '\0')
		(*format)++;
}

void	padding_with_c(int len, char c)
{
	while (len > 0)
	{
		write(1, &c, 1);
		len--;
	}
}
