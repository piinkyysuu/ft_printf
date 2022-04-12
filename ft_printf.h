/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:36:22 by thule             #+#    #+#             */
/*   Updated: 2022/04/12 14:48:13 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "libft/libft.h"
#include <stdio.h> //rmb to delete
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
	char sign;		// for negative number
	char specifier; // diouxX f csp
	char minus;		// flag -
	char plus;		// flag +
	char space;		// flag (space)
	char zero;		// flag 0
	char hashtag;	// flag #
	int counter;
	int number_len;
} t_proto;

typedef void specifier_handler(t_proto *p, va_list *arg);

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
void delete_space(const char **format);
void length(const char **format, t_proto *p);
void flags(const char **format, t_proto *p);

// string_and_char.c
void print_single_character(t_proto *p, va_list *arg);
void print_string(t_proto *p, va_list *arg);

// signed_conversion.c
void signed_conversion(t_proto *p, va_list *arg);
void print_signed_conversion(t_proto *p, long long int n);

// unsigned_conversion.c
void case_0(t_proto *p);
void unsigned_conversion(t_proto *p, va_list *arg);
void print_unsigned_conversion(t_proto *p, unsigned long long int n);

void print_address(t_proto *p, va_list *arg);

// printing_utils.c
void padding_with_c(int len, char c);
void field_width(t_proto *p);
void printer_helper(t_proto *p);
void	print_number_conversion(unsigned long long n, int base, t_proto *p);

// number_utils.c
int number_len(unsigned long long int n, int base);
void print_number(unsigned long long int n, int base, t_proto *p);
int assign_base(t_proto *p);

// to delete later:
void print_prototype(t_proto *p);

#endif
