/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:02:06 by thule             #+#    #+#             */
/*   Updated: 2022/04/10 02:56:08 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	prototype_initializer(t_proto *p)
{
	ft_bzero(p->length, 3);
	p->width		=	0;
	p->precision	=	-1;
	p->prefix		=	"\0";
	p->sign			=	'\0';
	p->specifier	=	'\0';
	p->minus		=	'\0';
	p->plus			=	'\0';
	p->space		=	'\0';
	p->zero			=	'\0';
	p->hashtag		=	'\0';
	p->counter 		=	0;
	p->number_len	=	0;
}

void	flags(const char **format, t_proto *p)
{
	while (**format == '-' || **format == '+' || **format == ' ' || 
			**format == '#' || **format == '0')
	{
		p->minus += (**format == '-');
		p->plus += (**format == '+');
		p->space += (**format == ' ');
		p->zero += (**format == '0');
		p->hashtag += (**format == '#');
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

void	delete_space(const char **format)
{
	while (**format == ' ' && **format != '\0')
		(*format)++;
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
	delete_space(format);
	if (**format == '.')
	{
		(*format)++;
		delete_space(format);
		p->precision = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	delete_space(format);
	length(format, p);
	delete_space(format);
	p->specifier = **format;
}