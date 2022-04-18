/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floating_point_conversion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 23:50:20 by thule             #+#    #+#             */
/*   Updated: 2022/04/18 22:38:43 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

typedef struct	s_float
{
	uint8_t sign;
	uint16_t exponent;
	uint64_t fraction;
	char *first_part;
	char *second_part;
}	t_float;

int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

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

void	print_arr(uint8_t *arr, int amount)
{
	int index = 0;
	while (index < amount)
	{
		printf("%d", arr[index]);
		index++;
	}
	printf("\n\n");
}

void	divide_by_2(uint8_t *arr, int len)
{
	int	remainder;
	int	index;
	int last_value;

	remainder = 0;
	index = 0;
	last_value = 0;
	while (index < len)
	{
		last_value = arr[index];
		arr[index] = ((remainder * 10) + arr[index]) / 2;
		if (last_value % 2 == 0)
			remainder = 0;
		else
			remainder = 1;
		index++;
	}
}

void	add_array(uint8_t *arr, uint8_t *res, int len)
{
	len = len - 1;
	while (len >= 0)
	{
		res[len] = res[len] + arr[len];
		if (res[len] >= 10 && len != 0)
		{
			res[len - 1]++;
			res[len] -= 10;
		}
		len--;
	}
}

char	*create_fraction_str(char *fraction_part, uint8_t *res)
{
	int precision = 20;
	int index = 0;

	fraction_part = (char *)malloc(sizeof(char) * (precision + 3));
	fraction_part[0] = '.';
	while (index < precision + 1)
	{
		fraction_part[index + 1] = res[index] + 48;
		index++;
	}
	fraction_part[index + 1] = '\0';
	return fraction_part;
}

char *handle_fraction_part(char *fraction_part, t_float *f, int amount_to_shift)
{
	uint8_t arr[1077];
	uint8_t res[1077];
	int		index;

	index = 63;
	ft_memset(&arr, 0, sizeof(uint8_t) * 1077);
	arr[0] = 5;
	ft_memset(&res, 0, sizeof(uint8_t) * 1077);
	if (amount_to_shift == 63)
		f->fraction = f->fraction << (amount_to_shift);
	else if (amount_to_shift >= -1)
		f->fraction = f->fraction << (amount_to_shift + 1);
	else
	{
		amount_to_shift = ft_abs(amount_to_shift + 1);
		while (amount_to_shift--)
			divide_by_2(arr, 1077);
	}
	print_amount_of_bits(f->fraction, 63);
	while (index >= 0)
	{
		if ((f->fraction >> index) & 1)
			add_array(arr, res, 1077);
		divide_by_2(arr, 1077);
		index--;
	}
	return create_fraction_str(fraction_part, res);
}

void	print_float(t_float *f, t_proto *p)
{
	int	counter;

	counter = 0;
	if (p->width > p->counter)
		counter = p->width - p->counter;
	if (!p->minus)
		padding_with_c(counter, ' ');
	write(1, p->prefix, ft_strlen(p->prefix));
	//maybe padding with 0 goes in between!
	write(1, f->first_part, ft_strlen(f->first_part));
	if (f->exponent != 2047)
		write(1, f->second_part, p->precision);
	if (p->minus)
		padding_with_c(counter, ' ');
	p->counter +=counter;
}

void	initialize_float_struct(t_float *f, uint64_t copy)
{
	f->sign = copy >> 63;
	f->exponent = (copy >> 52) & 2047;
	f->fraction = (copy << 11) | (1UL << 63);
	f->first_part = "";
	f->second_part = "";
}

void	special_cases(t_float *f, t_proto *p, uint64_t copy)
{
	if (copy << 12 == 0)
	{
		if (f->sign)
			p->prefix = "-";
		else if (p->plus)
			p->prefix = "+";
		f->first_part = "inf";
	}
	else
		f->first_part = "nan";
	p->counter = ft_strlen(f->first_part) + ft_strlen(p->prefix);
	print_float(f, p);
}

void	calculate_frac(t_float *f, uint8_t *res)
{
	uint8_t	arr[1077];
	int		amount;
	int		index;
	
	index = 63;
	ft_memset(arr, 0, 1077);
	arr[0] = 5;
	amount = (int)f->exponent - 1023;
	if (amount == 63)
		f->fraction = f->fraction << amount;
	else if (amount >= -1)
		f->fraction = f->fraction << (amount + 1);
	else
	{
		amount = ft_abs(amount + 1);
		while (amount--)
			divide_by_2(arr, 1077);
	}
	while (index >= 0)
	{
		if ((f->fraction >> index) & 1)
			add_array(arr, res, 1077);
		divide_by_2(arr, 1077);
		index--;
	}
}

char	*frac_part(t_float *f, t_proto *p)
{
	char		*str;
	int			index;
	uint8_t		res[1077];
	
	index = 0;
	ft_memset(res, 0, 1077);
	str = (char *)malloc(sizeof(char) * (p->precision + 3));
	if (str)
	{
		str[0] = '.';
		calculate_frac(f, res);
		while (index < p->precision + 1)
		{
			str[index + 1] = res[index] + 48;
			index++;
		}
		str[index + 1] = '\0';
	}
	return str;
}

void	other_cases(t_float *f, t_proto *p, long double n)
{
	if (n < 0)
	{
		n = -n;
		p->prefix = "-";
	}
	f->first_part = ft_ulltoa(n);
	if ((unsigned long long int)n == ULLONG_MAX)
		f->first_part[19]++;
	f->second_part = frac_part(f, p);
	printf("%s", f->second_part);
}

void	floating_point_conversion(t_proto *p, va_list *arg)
{
	long double		n;
	uint64_t		copy;
	t_float			f;
	
	if (p->precision < 0)
		p->precision = 6;
	n = (long double)va_arg(*arg, long double);
	if (ft_strcmp(p->length, "L"))
		n = (double)n;
	ft_memcpy(&copy, &n, sizeof(uint64_t));
	initialize_float_struct(&f, copy);
	if (f.exponent == 2047)
		special_cases(&f, p, copy);
	else
		other_cases(&f, p, n);
	
	// char		*final_string;
	// char		*integer_part;
	// char		*fraction_part;
	// t_float		f;

	// long double a = -1.0;
	// uint64_t b;
	// ft_memcpy(&b, &a, sizeof(uint64_t));
	// print_bit(b);
	// printf("printf value: %s%020f%s\n", GREEN, a, WHITE);

	// f.sign = b >> 63;
	// f.exponent = (b >> 52) & 2047;
	// f.fraction = (b << 11) | (1UL << 63);

	// if (f.exponent == 2047 && (b << 12) == 0)
	// 	final_string = "inf";
	// else if (f.exponent == 2047 && (b << 12) != 0)
	// 	final_string = "nan";
	// else
	// {
	// 	if (a < 0)
	// 	a = -a;
	// 	integer_part = ft_ulltoa(a);
	// 	if ((unsigned long long int)a == ULLONG_MAX)
	// 		integer_part[19]++;
	// 	int amount_to_shift = (int)f.exponent - 1023;
	// 	fraction_part = handle_fraction_part(fraction_part, &f, amount_to_shift);
	// 	final_string = ft_strjoin(integer_part, fraction_part);
	// }
}