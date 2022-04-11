/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:35:18 by thule             #+#    #+#             */
/*   Updated: 2022/04/10 02:35:44 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	padding(int	len, char c)
{
	while (len)
	{
		write(1, &c, 1);
		len--;
	}
}

void	field_width(t_proto *p)
{
	if (p->width > p->counter)
	{
		padding(p->width - p->counter, ' ');
		p->counter += p->width - p->counter;
	}
}