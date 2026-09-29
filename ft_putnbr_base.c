/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salegari <salegari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:45:21 by salegari          #+#    #+#             */
/*   Updated: 2026/09/29 19:43:45 by salegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_checkbase(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (i > 1);
}

int	ft_putnbr_base(int nbr, char *base)
{
	unsigned int	n;
	int				len;
	int				count;

	count = 0;
	if (!ft_checkbase(base))
		return (0);
	len = 0;
	while (base[len])
		len++;
	n = nbr;
	if (n >= (unsigned int)len)
		count += ft_putnbr_base(n / len, base);
	count += ft_intpchar(base[n % len]);
	return (count);
}
