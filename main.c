/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:55:03 by thule             #+#    #+#             */
/*   Updated: 2022/04/12 16:25:08 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void print_prototype(t_proto *p)
{
	printf("%s____PRINT_PROTOTYPE____%s\n", MAGENTA, WHITE);
	printf("minus		%d\n", p->minus);
	printf("plus		%d\n", p->plus);
	printf("space		%d\n", p->space);
	printf("zero		%d\n", p->zero);
	printf("hashtag		%d\n", p->hashtag);
	printf("width		%d\n", p->width);
	printf("precision	%d\n", p->precision);
	printf("length		%s\n", p->length);
	printf("specifier	%c\n", p->specifier);
}


void print_address(t_proto *p, va_list *arg)
{
	unsigned long long n;

	n = va_arg(*arg, unsigned long long);
	p->number_len = number_len(n, 16);
	p->counter = p->number_len + 2;
	if (!p->minus)
		field_width(p);
	write(1, "0x", 2);
	print_number(n, 16, p);
	if (p->minus)
		field_width(p);
}

int main()
{
	int lib = 0;
	int ft = 0;
	char *s = NULL;

	printf("%05.d", 30);

	// F("083.[%0#+10d]\t\t\t", -42);

	// printf("[%.d, %.0d]", 0, 0);

	// printf("hhd	is	%lu\n", sizeof(signed char));
	// printf("hd	is	%lu\n", sizeof(short int));
	// printf("d	is	%lu\n", sizeof(int));
	// printf("ld	is	%lu\n", sizeof(long int));
	// printf("lld	is	%lu\n\n", sizeof(long long int));

	// printf("hhu	is	%lu\n", sizeof(unsigned char));
	// printf("hu	is	%lu\n", sizeof(unsigned short int));
	// printf("u	is	%lu\n", sizeof(unsigned int));
	// printf("lu	is	%lu\n", sizeof(unsigned long int));
	// printf("llu	is	%lu\n\n", sizeof(unsigned long long int));

	// printf("f	is	%lu\n", sizeof(double));
	// printf("Lf	is	%lu\n", sizeof(long double));


	// F("%p", "hello");
	// //CASES THAT NEED FIXING:
	//  F("3.|%0.4u|", 0);
	// F("008.[% d]", 42);
	// F("001.[%#08.2x]", 52);
	// F("009.[%-010.5d]", 42);




	// F("58.[%20.20x]\t", -1234);
	// ft_printf("%+-#20.31d %LLp %.20% %-.3f", "something");

	// F("% c", 50);
	// unsigned int blah = 2012;
	// F("%#2x", blah);
	// F("|%10.0d|", 0);
	// F("%+.5d", 200000);
	// F("|%10c %%|", 'A');
	// F("|%-30s %-10c %%|", "Anh Thu haha", 'j');

	// ft = printf('');
	// printf("\n%d", ft);

	// int a = printf("%", 2);
	// printf("\n%d", a);

	// printf("%d", ft_atoi("20"));
	// F("%010.s", "moah");

	// F("017:[%.s]", -5, "42");

	// printf("%.3f\n", 0.5596);
	// printf("%f %f %f", 0.5, 1.5, 2.5);

	// char *t = ft_ulltoa(-2);
	// ft_printf("%p", s);
	// printf("\n%lld %p", s, s);

	char c = 'e';
	s = "hello";
	int n = 202;

	// TEST FPR C,S,P
	//  F("1.|%c %c %c		|", c, '2', 'e');
	//  F("2.|%10.10s|", s);
	//  F("3.|%10.0s %c %10.10s %2c|", "ayoo", c, s, 'e');
	//  F("4.|%-25s %+d %c|", s, INT_MAX, c);
	//  F("5.|%p|", &n);
	//  F("6.|%lld %+p|", &n, &n);
	//  F("7.|%020s|", s);

	// // TEST FOR D
	//  F("01.[%d]\t\t\t", 123);
	//  F("02.[%d]\t\t\t", -123);
	//  F("03.[%d]\t\t", -2147483648);
	//  F("04.[%d]\t\t\t", 2147483647);
	//  F("05.[%.0d]\t\t", -2147483648);
	//  F("08.[%.20d]\t", -214);
	//  F("09.[%.d]\t\t", -2147483648);
	//  F("10.[%10.d]\t\t", -2147483648);
	//  F("11.[%20.d]\t", -2147483648);
	//  F("12.[%0.0d]\t\t", -2147483648);
	//  F("13.[%5.0d]\t\t", -2147483648);
	//  F("14.[%10.0d]\t\t", -2147483648);
	//  F("15.[%20.0d]\t", -2147483648);
	//  F("16.[%0.0d]\t\t", -2147483648);
	//  F("17.[%0.5d]\t\t", -2147483648);
	//  F("18.[%0.10d]\t\t", -2147483648);
	//  F("19.[%0.20d]\t", -2147483648);
	//  F("20.[%5.0d]\t\t", -2147483648);
	//  F("21.[%5.5d]\t\t", -2147483648);
	//  F("22.[%5.10d]\t\t", -2147483648);
	//  F("23.[%5.20d]\t", -2147483648);
	//  F("24.[%10.0d]\t\t", -2147483648);
	//  F("25.[%10.5d]\t\t", -2147483648);
	//  F("26.[%10.10d]\t\t", -2147483648);
	//  F("27.[%10.20d]\t", -2147483648);
	//  F("28.[%20.0d]\t", -2147483648);
	//  F("29.[%20.5d]\t", -2147483648);
	//  F("30.[%20.10d]\t", -2147483648);
	//  F("31.[%20.20d]", -2147483648);
	//  F("32.[%10d]\t\t\t", 0);
	//  F("34.[%10.0d]\t\t\t", 0);
	//  F("35.[%.0d]\t\t\t\t", 0);
	//  F("36.[%10.0d]\t\t\t", 10);
	//  F("37.[%.0d]\t\t\t", -120);
	//  F("38.[%.20d]\t", -2147483648);
	//  F("39.|%010d|", 20);
	//  F("40.[%+ 3d]", 20);

	// // TEST FOR U
	//  F("1.|%u|", -2);
	//  F("2.|%0.0u|", 0);
	//  F("3.|%0.4u|", 0);
	//  F("4.|%10u|", LONG_MIN);
	//  F("5.|%0.0u|", 0);
	//  F("6.|%-+10.5u|", 12);
	//  F("7.|%+20.20u|", -50);
	//  F("8.|%+u|", 'a');
	//  F("9.|%llu|", 'a');
	//  F("10.|%+hu|", 'a');
	//  F("11.|%-20.2hhu|", ULLONG_MAX);
	//  F("12.|%llu|", LLONG_MIN);
	//  F("13.|%hu|", LLONG_MIN);
	//  F("14.|%u %hu %hhu %lu %llu|", LONG_MIN, LONG_MIN, 2);
	//  F("15.|%-100.12u This is something?|", 20);

	// // // TEST FOR O, x, X
	// F("1.|%#.0x|", 0);
	// F("2.|%llo|", ULLONG_MAX);
	// F("3.|%#.6llo|", 2590);
	// F("4.|%.10lx|", 2414);
	// F("5.|%.10lX|", 2414);
	// F("6.|%#.10lx|", 2414);
	// F("7.|%#.10lX|", 2414);
	// F("8.|%#x|", 0);
	// F("9.|%#.30X|", 7480);
	// F("10.|%.0x|", 0);

	// F("01.[%x]\t\t\t\t", 123);
	// F("02.[%x]\t\t\t", -123);
	// F("03.[%x]\t\t\t", -2147483648);
	// F("04.[%x]\t\t\t", 2147483647);
	// F("05.[%.0x]\t\t\t", -2147483648);
	// F("06.[%.5x]\t\t\t", -2147483648);
	// F("07.[%.10x]\t\t\t", -2147483648);
	// F("08.[%.20x]\t", -2147483648);
	// F("09.[%.x]\t\t\t", -2147483648);
	// F("10.[%10.x]\t\t\t", -2147483648);
	// F("11.[%20.x]\t", -2147483648);
	// F("12.[%0.0x]\t\t\t", -2147483648);
	// F("13.[%5.0x]\t\t\t", -2147483648);
	// F("14.[%10.0x]\t\t\t", -2147483648);
	// F("15.[%20.0x]\t", -2147483648);
	// F("16.[%0.0x]\t\t\t", -2147483648);
	// F("17.[%0.5x]\t\t\t", -2147483648);
	// F("18.[%0.10x]\t\t\t", -2147483648);
	// F("19.[%0.20x]\t", -2147483648);
	// F("20.[%5.0x]\t\t\t", -2147483648);
	// F("21.[%5.5x]\t\t\t", -2147483648);
	// F("22.[%5.10x]\t\t\t", -2147483648);
	// F("23.[%5.20x]\t", -2147483648);
	// F("24.[%10.0x]\t\t\t", -2147483648);
	// F("25.[%10.5x]\t\t\t", -2147483648);
	// F("26.[%10.10x]\t\t\t", -2147483648);
	// F("27.[%10.20x]\t", -2147483648);
	// F("28.[%20.0x]\t", -2147483648);
	// F("29.[%20.5x]\t", -2147483648);
	// F("30.[%20.10x]\t", -2147483648);
	// F("31.[%20.20x]\t", -2147483648);
	// F("32.[%.0x]\t\t\t", -1234);
	// F("33.[%.5x]\t\t\t", -1234);
	// F("34.[%.10x]\t\t\t", -1234);
	// F("35.[%.20x]\t", -1234);
	// F("36.[%.x]\t\t\t", -1234);
	// F("37.[%10.x]\t\t\t", -1234);
	// F("38.[%20.x]\t", -1234);
	// F("39.[%0.0x]\t\t\t", -1234);
	// F("40.[%5.0x]\t\t\t", -1234);
	// F("41.[%10.0x]\t\t\t", -1234);
	// F("42.[%20.0x]\t", -1234);
	// F("43.[%0.0x]\t\t\t", -1234);
	// F("44.[%0.5x]\t\t\t", -1234);
	// F("45.[%0.10x]\t\t\t", -1234);
	// F("46.[%0.20x]\t", -1234);
	// F("47.[%5.0x]\t\t\t", -1234);
	// F("48.[%5.5x]\t\t\t", -1234);
	// F("49.[%5.10x]\t\t\t", -1234);
	// F("50.[%5.20x]\t", -1234);
	// F("51.[%10.0x]\t\t\t", -1234);
	// F("52.[%10.5x]\t\t\t", -1234);
	// F("53.[%10.10x]\t\t\t", -1234);
	// F("54.[%10.20x]\t", -1234);
	// F("55.[%20.0x]\t", -1234);
	// F("56.[%20.5x]\t", -1234);
	// F("57.[%20.10x]\t", -1234);
	// F("58.[%20.20x]\t", -1234);
	// F("59.[%10x]\t\t\t", 0);
	// F("60.[%10x]\t\t\t", 0);
	// F("61.[%10.0x]\t\t\t", 0);
	// F("62.[%.0x]\t\t\t\t", 0);
	// F("63.[%10.0x]\t\t\t", 10);
	// F("64.[%.0x]\t\t\t", -120);



	// printf("====part 1====\n");
	// F("001.[%#-1.0x]", 0);
	// F("002.[%#-1.0u]", 0);
	// F("003.[%#.o %#.0o]", 0, 0);
	// F("004.[%.o]", 0);
	// F("005.[%.x %.0x]", 0, 0);
	// F("006.[%#.x]", 0);
	// F("007.[%#.X]", 0);
	// F("008.[%#o]", 0);
	// F("009.[%#o]", 0);
	// F("010.[%#.3o]", 1);
	// F("011.[%o]", 0);
	// F("012.[%05o]", 42);
	// F("013.[%#-1.0X]", 0);
	// F("014.[%#08.2o]", 52);
	// F("015.[%08.2o]", 52);
	// F("016.[%#8d]", 42);
	// F("017.[% -1.0d, % -1.0i]", 0, 0);
	// F("018.[%#-1.0o]", 0);
	// printf("====part 2====\n");
	// F("002.[%#08.x]", 52);
	// F("003.[%08.2x]", 52);
	// F("005.[% u]", 4294967295);
	// F("006.[%#+08x]", 42);
	// F("007.[%#+08X]", 42);
	// F("069.[%08.X]", 42);
	// F("069.[%015.p]", 42);
	// F("083.[%0#+            10d]\t\t\t", -42);
	// F("001.[%hd]", 32767);
	// F("002[%010d]", -42);
	// F("016.[%#X]", 0); 
	// F("017.[%.d, %.0d]", 0, 0);
	// F("012.[%#o]", 0);
	// F("013.[%#.3o]", 1);
	// F("016.[%o, %ho, %hho]", -42, -42, -42);
	// F("017.[% i]", 9999);
	// F("019.[%#6o]", 2500);
	// F("020.[%#.o %#.0o]", 0, 0);
	// F("025.[% .3d]", 5, 0);
	// F("026.[%    53d]", 5, 0);
	// F("027.[%#.3o]", 1);
	// F("029.[% 03d]", 0);
	// F("030.[%5p]", 0);
	// F("032.[%10.5d]", 42);
	// F("034.[%#o]", 0);
	// F("035.[%hd]", -42);
	// F("036.[%lld]", 32768);
	// F("037.[%hhd]", -129);
	// F("038.[% ]");
	// F("039.[%hhx]", 128);
	// F("040.[%-5%]");
	// F("041.[%03.2d]", 1);
	// F("042.[%03.2d]", -1);
	// F("043.[%3.2d]", -1);
	// F("044.[%010.2d]", 1);
	// F("047.[%hd]", 32768);
	// F("048.[%10hhd]", -129);
	// F("049.[%hd]", 32767);
	// F("050.[%hhd]", 128);
	// F("051.[%hhd]", -128);
	// F("052.[%d]", 2147483647);
	// F("053.[%hhd]", 128);
	// F("054.[% d]\t", -42);
	// F("055.[% d]\t", 42);
	// F("056.[% 10.3d]\t", 0);
	// F("057.[%#.x %#.0x]", 0, 0);
	// F("058.[%d]", -1);
	// F("059.[%o]", 40);
	// F("060.[%#6o]", 2500);
	// F("061.[%+d]", 0);
	// F("062.[%hd]", 32768);
	// F("063.[%hhd]", 128);
	// F("064.[%10.5ho]", 4294967296);
	// F("065.[%10.5ho]", 4294967296);
	// F("066.[%############x]", 42);
	// F("067.[%#x]", 0);
	// F("068.[%s %s]\t", "this", "is");
	// F("070.[%s %s %s]\t", "this", "is", "a");
	// F("071.[%lx]\t\t", 4294967296);
	// F("072.[%llX]\t\t", 4294967296);
	// F("073.[%X]", 4294967296);
	// F("074.[%x]", -42);
	// F("075.[%#x]\t\t\t", 42);
	// F("076.[%d]\t\t\t", 42);
	// F("077.[%5%]");
	// F("078.[%5%]\t\t\t", 42);
	// F("079.[%#d]\t\t\t", 42);
	// F("080.[%#p]\t\t\t", 42);
	// F("081.[foo%%s]\t\t\t");
	// F("082.[Hello World%%s]\t\t");
	// F("084.[%+00000010d]\t\t\t", 42);
	// F("085.[%--+--+10d]\t\t\t", 42);
	// F("086.[%----+--10d]\t\t\t", 42);
	// F("087.[%]");
	// F("088.[%x]\t\t\t", 4294967295);
	// F("100.[%p]", ULONG_MAX);
	// F("101.[%u]", -1);
	// F("102.[%p]", -42);
	// F("103.[%p]", LONG_MAX);
	// F("104.[%p]", -ULONG_MAX);
	// F("105.[%- -- - + --   10.4d]\t\t\t", 42);
	// F("106.[%s ]", "");
	// F("02.[%d]\t\t\t", -123);
	// F("03.[%d]\t\t", -2147483648);
	// F("04.[%d]\t\t\t", 2147483647);
	// F("05.[%.0d]\t\t", -2147483648);
	// F("08.[%.20d]\t", -214);
	// F("09.[%.d]\t\t", -2147483648);
	// F("10.[%10.d]\t\t", -2147483648);
	// F("11.[%20.d]\t", -2147483648);
	// F("12.[%0.0d]\t\t", -2147483648);
	// F("13.[%5.0d]\t\t", -2147483648);
	// F("14.[%10.0d]\t\t", -2147483648);
	// F("15.[%20.0d]\t", -2147483648);
	// F("16.[%0.0d]\t\t", -2147483648);
	// F("17.[%0.5d]\t\t", -2147483648);
	// F("18.[%0.10d]\t\t", -2147483648);
	// F("19.[%0.20d]\t", -2147483648);
	// F("20.[%5.0d]\t\t", -2147483648);
	// F("21.[%5.5d]\t\t", -2147483648);
	// F("22.[%5.10d]\t\t", -2147483648);
	// F("23.[%5.20d]\t", -2147483648);
	// F("24.[%10.0d]\t\t", -2147483648);
	// F("25.[%10.5d]\t\t", -2147483648);
	// F("26.[%10.10d]\t\t", -2147483648);
	// F("27.[%10.20d]\t", -2147483648);
	// F("28.[%20.0d]\t", -2147483648);
	// F("29.[%20.5d]\t", -2147483648);
	// F("30.[%20.10d]\t", -2147483648);
	// F("31.[%20.20d]\t", -2147483648);
	// F("32.[%10d]\t\t\t", 0);
	// F("33.[%10.d]\t\t\t", 0);
	// F("34.[%10.0d]\t\t\t", 0);
	// F("35.[%.0d]\t\t\t\t", 0);
	// F("36.[%10.0d]\t\t\t", 10);
	// F("37.[%.0d]\t\t\t", -120);
	// F("38.[%.20d]\t", -2147483648);
	// //%s
	// printf("====s====\n");
	// F("01.[%010.2s]\t\t\t", "Hello world");
	// F("03.[%015.2s]\t\t\t", "hoge");
	// F("04.[%3.10s]\t\t\t", "hoge");
	// F("05.[%-010.10s]\t\t\t", "hoge");
	// F("06.[%+10.0s]\t\t\t", "hoge");
	// F("07.[%s]\t\t\t\t", "");
	// F("08.[%10.2s]\t\t\t", NULL);
	// F("09.[%3.2s]\t\t\t", NULL);
	// F("10.[%+3.10s]\t\t\t", NULL);
	// F("11.[%-3.10s]\t\t\t", NULL);
	// F("12.[%+10.0s]\t\t\t", NULL);
	// printf("====c====\n");
	// F("01.[%c]\t\t\t\t", 'h');
	// F("02.[%-10.2c]\t\t\t", 'h');
	// F("03.[%05.2c]\t\t\t", 'h');
	// F("04.[%3.10c]\t\t\t", 'h');
	// F("05.[%-0.10c]\t\t\t\t", 'h');
	// F("06.[%+10.0c]\t\t\t", 'h');
	// F("07.[%c]\t\t\t\t", 0);
	// F("08.[%10.2c]\t\t", NULL);
	// F("09.[%3.2c]\t\t\t", NULL);
	// F("10.[%+3.10c]\t\t\t", NULL);
	// F("11.[%-3.10c]\t\t\t", NULL);
	// F("12.[%+10.0c]\t\t", NULL);
	// printf("====x====\n");
	// F("01.[%x]\t\t\t\t", 123);
	// F("02.[%x]\t\t\t", -123);
	// F("03.[%x]\t\t\t", -2147483648);
	// F("04.[%x]\t\t\t", 2147483647);
	// F("05.[%.0x]\t\t\t", -2147483648);
	// F("06.[%.5x]\t\t\t", -2147483648);
	// F("07.[%.10x]\t\t\t", -2147483648);
	// F("08.[%.20x]\t", -2147483648);
	// F("09.[%.x]\t\t\t", -2147483648);
	// F("10.[%10.x]\t\t\t", -2147483648);
	// F("11.[%20.x]\t", -2147483648);
	// F("12.[%0.0x]\t\t\t", -2147483648);
	// F("13.[%5.0x]\t\t\t", -2147483648);
	// F("14.[%10.0x]\t\t\t", -2147483648);
	// F("15.[%20.0x]\t", -2147483648);
	// F("16.[%0.0x]\t\t\t", -2147483648);
	// F("17.[%0.5x]\t\t\t", -2147483648);
	// F("18.[%0.10x]\t\t\t", -2147483648);
	// F("19.[%0.20x]\t", -2147483648);
	// F("20.[%5.0x]\t\t\t", -2147483648);
	// F("21.[%5.5x]\t\t\t", -2147483648);
	// F("22.[%5.10x]\t\t\t", -2147483648);
	// F("23.[%5.20x]\t", -2147483648);
	// F("24.[%10.0x]\t\t\t", -2147483648);
	// F("25.[%10.5x]\t\t\t", -2147483648);
	// F("26.[%10.10x]\t\t\t", -2147483648);
	// F("27.[%10.20x]\t", -2147483648);
	// F("28.[%20.0x]\t", -2147483648);
	// F("29.[%20.5x]\t", -2147483648);
	// F("30.[%20.10x]\t", -2147483648);
	// F("31.[%20.20x]\t", -2147483648);
	// F("32.[%.0x]\t\t\t", -1234);
	// F("33.[%.5x]\t\t\t", -1234);
	// F("34.[%.10x]\t\t\t", -1234);
	// F("35.[%.20x]\t", -1234);
	// F("36.[%.x]\t\t\t", -1234);
	// F("37.[%10.x]\t\t\t", -1234);
	// F("38.[%20.x]\t", -1234);
	// F("39.[%0.0x]\t\t\t", -1234);
	// F("40.[%5.0x]\t\t\t", -1234);
	// F("41.[%10.0x]\t\t\t", -1234);
	// F("42.[%20.0x]\t", -1234);
	// F("43.[%0.0x]\t\t\t", -1234);
	// F("44.[%0.5x]\t\t\t", -1234);
	// F("45.[%0.10x]\t\t\t", -1234);
	// F("46.[%0.20x]\t", -1234);
	// F("47.[%5.0x]\t\t\t", -1234);
	// F("48.[%5.5x]\t\t\t", -1234);
	// F("49.[%5.10x]\t\t\t", -1234);
	// F("50.[%5.20x]\t", -1234);
	// F("51.[%10.0x]\t\t\t", -1234);
	// F("52.[%10.5x]\t\t\t", -1234);
	// F("53.[%10.10x]\t\t\t", -1234);
	// F("54.[%10.20x]\t", -1234);
	// F("55.[%20.0x]\t", -1234);
	// F("56.[%20.5x]\t", -1234);
	// F("57.[%20.10x]\t", -1234);
	// F("58.[%20.20x]\t", -1234);
	// F("59.[%10x]\t\t\t", 0);
	// F("60.[%10.x]\t\t\t", 0);
	// F("61.[%10.0x]\t\t\t", 0);
	// F("62.[%.0x]\t\t\t\t", 0);
	// F("63.[%10.0x]\t\t\t", 10);
	// F("64.[%.0x]\t\t\t", -120);

	return (0);
}
