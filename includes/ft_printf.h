/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:36:22 by thule             #+#    #+#             */
/*   Updated: 2022/09/13 09:22:57 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct s_proto
{
	char	length[3];
	char	*prefix;
	int		width;
	int		precision;
	int		zero_padding;
	int		base;
	char	specifier;
	char	minus;
	char	plus;
	char	space;
	char	zero;
	char	hashtag;
}	t_proto;

typedef struct s_float
{
	uint8_t		sign;
	uint16_t	exponent;
	uint64_t	fraction;
	char		*int_part;
	char		*frac_part;
}	t_float;

typedef int	t_specifier_handler(t_proto *p, va_list *arg);

enum e_function
{
	f_c,
	f_s,
	f_p,
	f_d,
	f_i,
	f_o,
	f_u,
	f_x,
	f_X,
	f_f,
	f_percentage,
	f_invalid
};

/* ft_printf.c */
int		ft_printf(const char *format, ...);
int		central_dispatch(t_proto *p, va_list *arg);

/* prototype.c */
void	prototype_initializer(t_proto *p);
void	prototype_handler(const char **format, t_proto *p);
void	skip_space(const char **format);
void	length(const char **format, t_proto *p);
void	flags(const char **format, t_proto *p);

/* address_char_str.c */
int		print_character(t_proto *p, va_list *arg);
int		print_string(t_proto *p, va_list *arg);
int		print_address(t_proto *p, va_list *arg);

/* signed_conversion.c */
int		signed_prefix(t_proto *p, long long int n);
int		signed_conversion(t_proto *p, va_list *arg);
int		signed_conversion_helper(t_proto *p, long long int n);

/* unsigned_conversion.c */
int		unsigned_prefix(t_proto *p, unsigned long long int n, int nbr_len);
int		unsigned_conversion(t_proto *p, va_list *arg);
int		unsigned_conversion_helper(t_proto *p, unsigned long long int n);

/* float_conversion.c */
int		float_conversion(t_proto *p, va_list *arg);
int		float_other_cases(t_proto *p, t_float *f);
int		float_special_cases(t_float *f, t_proto *p, uint64_t format);

/* float_utils.c */
void	divide_by_2(uint8_t *arr, int len);
void	add_array(uint8_t *arr, uint8_t *res, int len);
void	mutiply_by_2(uint8_t *arr, int len);
void	integer_plus_1(u_int8_t *int_arr);
int		float_prefix(t_float *f, t_proto *p);

/* float_utils_2.c */
int		print_float(t_float *f, t_proto *p, int reserved_len);
void	initialize_float_struct(t_float *f, uint64_t format);

/* rounding.c */
void	rounding(t_float *f, uint8_t *int_arr, int precision, char hashtag);

/* create_frac_part.c */
char	*create_frac_part(t_float *f, int precision);
char	*frac_str(uint8_t *res, int size);
void	calc_frac_part(uint64_t frac_bit, uint8_t *res, int to_shift);

/* create_int_part.c */
void	create_int_part(t_float *f, uint8_t *res);
char	*int_str(uint8_t *res);
void	calc_int_part(uint64_t int_bit, uint8_t *res, int to_shift);

/* number_utils.c */
int		number_len(unsigned long long int n, int base);
void	print_number(unsigned long long int n, int base, t_proto *p);
int		zero_padding_value(t_proto *p, int nbr_len, int prefix_len);
int		print_number_conversion(unsigned long long n, t_proto *p, \
								int reserved_len);

/* utils.c */
int		assign_base(char c);
void	skip_space(const char **format);
void	padding_with_c(int len, char c);

#endif
