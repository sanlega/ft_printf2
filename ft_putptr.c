/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salegari <salegari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:52:38 by salegari          #+#    #+#             */
/*   Updated: 2026/09/29 19:42:30 by salegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putptr_base(unsigned long nbr, char *base)
{
	int	len;
	int	count;

	len = ft_strlen(base);
	count = 0;
	if (nbr >= (unsigned long)len)
	{
		count += ft_putptr_base(nbr / len, base);
		count += ft_putptr_base(nbr % len, base);
	}
	else
	{
		count += ft_intpchar(base[nbr]);
	}
	return (count);
}

int	ft_putptr(void *ptr)
{
	int		count;
	char	*base;

	base = "0123456789abcdef";
	if (!ptr)
		return (ft_intpstr("(nil)"));
	count = ft_intpchar('0');
	count += ft_intpchar('x');
	count += ft_putptr_base((unsigned long)ptr, base);
	return (count);
}
