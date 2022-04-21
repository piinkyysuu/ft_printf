/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 23:50:20 by thule             #+#    #+#             */
/*   Updated: 2022/04/20 17:36:51 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void print_bit(uint64_t num)
{
	int i = 63;
	while (i >= 0)
	{
		if (i == 51 || i == 62)
			printf(" ");
		if ((num >> i) & 1)
			printf("1");
		else
			printf("0");
		i--;
	}
	printf("\n");
}

void print_amount_of_bits(uint64_t num, int i)
{
	while (i >= 0)
	{
		if ((num >> i) & 1)
			printf("1");
		else
			printf("0");
		i--;
	}
	printf("\n");
}

void print_arr(uint8_t *arr, int amount)
{
	int index = 0;
	while (index < amount)
	{
		printf("%d", arr[index]);
		index++;
	}
	printf("\n\n");
}

int print_float(t_float *f, t_proto *p, int reserved_len, int prefix_len)
{
	int xspace;

	xspace = 0;
	if (p->width > reserved_len)
		xspace = p->width - reserved_len;
	if (!p->minus)
		padding_with_c(xspace, ' ');
	write(1, p->prefix, ft_strlen(p->prefix));
	padding_with_c(p->zero_padding, '0');
	write(1, f->int_part, ft_strlen(f->int_part));
	write(1, f->frac_part, ft_strlen(f->frac_part));
	if (p->minus)
		padding_with_c(xspace, ' ');
	return (reserved_len + xspace);
}

void initialize_float_struct(t_float *f, uint64_t copy)
{
	f->sign = copy >> 63;
	f->exponent = (copy >> 52) & 2047;
	f->fraction = (copy << 11) | (1UL << 63);
	f->int_part = "";
	f->frac_part = "";
}

int special_cases(t_float *f, t_proto *p, uint64_t copy)
{
	int prefix_len;
	int reserved_len;

	prefix_len = 0;
	if (copy << 12 == 0)
	{
		if (f->sign)
			p->prefix = "-";
		else if (p->plus)
			p->prefix = "+";
		f->int_part = "inf";
		prefix_len = ft_strlen(p->prefix);
	}
	else
		f->int_part = "nan";
	reserved_len = ft_strlen(f->int_part) + prefix_len;
	return (print_float(f, p, reserved_len, prefix_len));
}

// void rounding(t_float *f, t_proto *p, long double *n)
// {
// 	printf("%s", GREEN);
// 	printf("string:		%s\n", f->frac_part);
// 	printf("precision:	%d\n", p->precision);

// 	int index = p->precision;
// 	char *str = f->frac_part;
// 	unsigned long long nbr = *n;

// 	if (p->precision == 0)
// 	{
// 		if (str[index + 1] == '5')
// 		{
// 			if ((nbr % 2) != 0)
// 				(*n)++;
// 			else
// 			{
// 				str = str + 2;
// 				while (*str)
// 				{
// 					if (*str != '0')
// 					{
// 						(*n)++;
// 						break;
// 					}
// 					str++;
// 				}
// 			}
// 		}
// 		else if (str[index + 1] > '5')
// 			(*n)++;
// 		ft_bzero(f->frac_part, 20);
// 	}
// 	if (str[index + 1] >= '5')
// 	{
// 		int nbr = str[index] - 48;
// 		if (str[index] < '9' && (nbr % 2 != 0 || nbr == 0))
// 			str[index]++;
// 		else if (str[index] == '9')
// 		{
// 			while (str[index] == '9')
// 			{
// 				str[index] = '0';
// 				index--;
// 			}
// 			if (ft_isdigit(str[index]))
// 				str[index]++;
// 			else
// 				(*n)++;
// 		}
// 	}
// 	str[p->precision + 1] = '\0';
// }

int float_prefix(t_float *f, t_proto *p)
{
	if (f->sign)
		p->prefix = "-";
	else
	{
		if (p->plus)
			p->prefix = "+";
		else if (p->space)
			p->prefix = " ";
	}
	return (ft_strlen(p->prefix));
}

void	integer_plus_1(u_int8_t *int_arr)
{
	uint8_t one[39];

	ft_memset(one, 0, 39);
	one[38] = 1;
	add_array(one, int_arr, 39);
}

void	precision_0(uint8_t *int_arr, char *frac_str)
{
	int	index;

	index = 2;
	if (frac_str[1] == '5')
	{
		if (int_arr[38] % 2 != 0)
			integer_plus_1(int_arr);
		else
		{
			while (frac_str[index])
			{
				if (frac_str[index] != '0')
				{
					integer_plus_1(int_arr);
					break;
				}
				index++;
			}
		}
	}
	else if (frac_str[1] > '5')
		integer_plus_1(int_arr);
	ft_bzero(frac_str, ft_strlen(frac_str));
}

int	rounding(t_float *f, uint8_t *int_arr, int precision)
{
	char	*frac_str;
	int		index;

	index = precision;
	frac_str = f->frac_part;
	if (!precision)
		precision_0(int_arr, frac_str);
	else if (precision > 0)
	{
		if (frac_str[index + 1] >= '5')
		{
			if (frac_str[index] < '9')
				frac_str[index]++;
			else if (frac_str[index] == '9')
			{
				while (frac_str[index] == '9')
				{
					frac_str[index] = '0';
					index--;
				}
				if (ft_isdigit(frac_str[index]))
					frac_str[index]++;
				else
					integer_plus_1(int_arr);
			}
		}
	}
	return (0);
}

int float_conversion(t_proto *p, va_list *arg)
{
	long double n;
	uint64_t copy;
	t_float f;
	uint8_t int_arr[39];
	ft_memset(int_arr, 0, 39);

	if (p->precision < 0)
		p->precision = 6;
	n = (long double)va_arg(*arg, long double);
	if (ft_strcmp(p->length, "L"))
		n = (double)n;
	ft_memcpy(&copy, &n, sizeof(uint64_t));
	// print_bit(copy);
	initialize_float_struct(&f, copy);
	if (f.exponent == 2047)
		return special_cases(&f, p, copy);

	create_int_part(&f, int_arr);
	// print_arr(int_arr, 39);
	f.frac_part = create_frac_part(&f, p->precision);
	rounding(&f, int_arr, p->precision);
	f.int_part = int_str(int_arr);
	
	// if (!f.int_part || !f.frac_part)
	// 	return (-1);
	printf("int:	[%s]\n", f.int_part);
	printf("frac:	[%s]\n", f.frac_part);

	return (0);
}