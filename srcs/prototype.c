/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:02:06 by thule             #+#    #+#             */
/*   Updated: 2022/04/21 19:23:47 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	prototype_initializer(t_proto *p)
{
	ft_bzero(p->length, 3);
	p->width = 0;
	p->precision = -1;
	p->prefix = "";
	p->specifier = '\0';
	p->minus = '\0';
	p->plus = '\0';
	p->space = '\0';
	p->zero = '\0';
	p->hashtag = '\0';
	p->zero_padding = 0;
	p->base = 0;
}

void	flags(const char **format, t_proto *p)
{
	while (**format == '-' || **format == '+' || **format == ' '
		||**format == '#' || **format == '0')
	{
		if (!p->minus && **format == '-')
			p->minus++;
		else if (!p->plus && **format == '+')
			p->plus++;
		else if (!p->space && **format == ' ')
			p->space++;
		else if (!p->zero && **format == '0')
			p->zero++;
		else if (!p->hashtag && **format == '#')
			p->hashtag++;
		(*format)++;
	}
}

void	length(const char **format, t_proto *p)
{
	int	index;

	index = 0;
	while ((**format == 'l' || **format == 'h' || **format == 'L'))
	{
		if (index == 0 || (index == 1 && **format == (p->length)[index - 1]))
			(p->length)[index++] = **format;
		(*format)++;
	}
	(p->length)[index] = '\0';
}

void	prototype_handler(const char **format, t_proto *p)
{
	(*format)++;
	flags(format, p);
	if (ft_isdigit(**format))
	{
		p->width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	skip_space(format);
	if (**format == '.')
	{
		(*format)++;
		skip_space(format);
		p->precision = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	skip_space(format);
	length(format, p);
	skip_space(format);
	p->specifier = **format;
	p->base = assign_base(p->specifier);
}
