/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salegari <salegari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:09:20 by salegari          #+#    #+#             */
/*   Updated: 2026/09/29 19:48:40 by salegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_conver(char c, va_list args)
{
	if (c == 'c')
		return (ft_intpchar(va_arg(args, int)));
	if (c == 's')
		return (ft_intpstr(va_arg(args, char *)));
	if (c == 'd')
		return (ft_intpnbr(va_arg(args, int)));
	if (c == 'i')
		return (ft_intpnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_putnbr_unsg(va_arg(args, int)));
	if (c == 'x')
		return (ft_putnbr_base(va_arg(args, int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_putnbr_base(va_arg(args, int), "0123456789ABCDEF"));
	if (c == 'p')
		return (ft_putptr(va_arg(args, void *)));
	if (c == '%')
		return (ft_intpchar('%'));
	return (0);
}

static int	check_format(char *f, va_list args)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (f[i])
	{
		if (f[i] != '%' && (i == 0 || f[i - 1] != '%'))
		{
			len += ft_intpchar(f[i]);
			i++;
		}
		else if (f[i] == '%')
		{
			len += check_conver(f[i + 1], args);
			i += 2;
		}
		else
		{
			len += ft_intpchar(f[i]);
			i++;
		}
	}
	return (len);
}

int	ft_printf(char const *f, ...)
{
	va_list	args;
	int		len;

	va_start(args, f);
	len = check_format((char *)f, args);
	va_end(args);
	return (len);
}

// #include <stdio.h>
//
// int	main(void)
// {
// 	printf(" %p %p ", NULL, NULL);
// 	printf("\n");
// 	ft_printf(" %p %p ", 0, 0);
// 	ft_printf("\n");
// 	return 0;
// }
