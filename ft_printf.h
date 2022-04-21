/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:36:22 by thule             #+#    #+#             */
/*   Updated: 2022/04/20 17:24:56 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "libft/libft.h"
#include <stdio.h> //rmb to delete
#include <float.h> //rmb to delete
#include <stdarg.h>
#include <limits.h>

#define ABS(N) ((N < 0) ? (-N) : (N)) // need to be turned into a function

// uneccessary part, need to delete later
#define F(...) ({                                    \
	ft = ft_printf(__VA_ARGS__);                     \
	printf("\n");                                    \
	lib = printf(__VA_ARGS__);                       \
	if (ft != lib)                                   \
		printf("%s", RED);                           \
	else                                             \
		printf("%s", GREEN);                         \
	printf("\nft:%d lib:%d %s\n\n", ft, lib, WHITE); \
})

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"

typedef struct s_proto
{
	char length[3]; // either (blank), l, ll, h, hh or L
	char *prefix;
	int width;		// the minimum field width (width - strlen) and padded with (space)
	int precision;	// .(some numbers)
	char specifier; // diouxX f csp
	char minus;		// flag -
	char plus;		// flag +
	char space;		// flag (space)
	char zero;		// flag 0
	char hashtag;	// flag #
	int zero_padding;
	int base;
	int reserved_len;
	int number_len;
} t_proto;

typedef struct s_float
{
	uint8_t sign;
	uint16_t exponent;
	uint64_t fraction;
	char *int_part;
	char *frac_part;
} t_float;

typedef int specifier_handler(t_proto *p, va_list *arg);

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

int ft_printf(const char *format, ...);

// prototype.c
void prototype_initializer(t_proto *p);
void prototype_handler(const char **format, t_proto *p);
void skip_space(const char **format);
void length(const char **format, t_proto *p);
void flags(const char **format, t_proto *p);

// string_char_address.c
int print_character(t_proto *p, va_list *arg);
int print_string(t_proto *p, va_list *arg);
int print_address(t_proto *p, va_list *arg);

// signed_conversion.c
int signed_conversion(t_proto *p, va_list *arg);
int signed_conversion_helper(t_proto *p, long long int n);

// unsigned_conversion.c
int unsigned_conversion(t_proto *p, va_list *arg);
int unsigned_conversion_helper(t_proto *p, unsigned long long int n);

// float_conversion.c
int float_conversion(t_proto *p, va_list *arg);

// float_utils.c
void divide_by_2(uint8_t *arr, int len);
void add_array(uint8_t *arr, uint8_t *res, int len);
void mutiply_by_2(uint8_t *arr, int len);

// create_frac_part.c
char *create_frac_part(t_float *f, int precision);
char *frac_str(uint8_t *res, int size);
void calc_frac_part(uint64_t frac_bit, uint8_t *res, int to_shift);

// create_int_part.c
void create_int_part(t_float *f, uint8_t *res);
char *int_str(uint8_t *res);
void calc_int_part(uint64_t int_bit, uint8_t *res, int to_shift);

// printing_utils.c
void padding_with_c(int len, char c);

// number_utils.c
int number_len(unsigned long long int n, int base);
void print_number(unsigned long long int n, int base, t_proto *p);
int zero_padding_value(t_proto *p, int nbr_len, int prefix_len);
int print_number_conversion(unsigned long long n, t_proto *p, int reserved_len, int prefix_len);

// to delete later:
void print_prototype(t_proto *p);
void print_arr(uint8_t *arr, int amount);
void print_amount_of_bits(uint64_t num, int i);

#endif
