/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salegari <salegari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 19:07:19 by salegari          #+#    #+#             */
/*   Updated: 2026/09/29 19:10:45 by salegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>

int	ft_strlen(char *s);
int	ft_putptr(void *ptr);
int	ft_putnbr_unsg(unsigned int n);
int	ft_putnbr_base(int nbr, char *base);
int	ft_intpnbr(int n);
int	ft_intpstr(char *s);
int	ft_intpchar(char c);
int	ft_printf(char const *f, ...);

#endif
