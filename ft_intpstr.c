/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intpstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salegari <salegari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:35:18 by salegari          #+#    #+#             */
/*   Updated: 2026/09/29 18:57:57 by salegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_intpstr(char *s)
{
	int	i;

	if (!s)
		return (write(1, "(null)", 6), 6);
	i = 0;
	while (s[i])
	{
		ft_intpchar(s[i]);
		i++;
	}
	return (i);
}
