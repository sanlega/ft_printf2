/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intputnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salegari <salegari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:32:19 by salegari          #+#    #+#             */
/*   Updated: 2026/09/29 19:44:14 by salegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_intpnbr(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (ft_intpstr("-2147483648"));
	if (n < 0)
	{
		len += ft_intpchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		len += ft_intpnbr(n / 10);
		len += ft_intpnbr(n % 10);
	}
	else
		len += ft_intpchar(n + '0');
	return (len);
}
