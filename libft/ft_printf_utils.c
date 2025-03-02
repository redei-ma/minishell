/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:14:47 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/12 16:55:43 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

size_t	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
		i++;
	write(1, s, i);
	return (i);
}

int	ft_putnbr(long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (write(1, "0", 1));
	if (n < 0)
	{
		i += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		i += ft_putnbr(n / 10);
	i += ft_putchar((n % 10) + 48);
	return (i);
}

int	ft_puthex(long long n, char c)
{
	char	*base;
	int		i;

	i = 0;
	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n == 0)
		return (write(1, "0", 1));
	if (n >= 16)
		i += ft_puthex(n / 16, c);
	n %= 16;
	write(1, &base[n], 1);
	return (i + 1);
}

int	ft_putptr(unsigned long long n)
{
	char	*base;
	int		i;

	i = 0;
	base = "0123456789abcdef";
	if (n == 0)
		return (write(1, "(nil)", 5));
	if (n >= 16)
		i += ft_putptr(n / 16);
	if (i == 0)
	{
		write(1, "0x", 2);
		i += 2;
	}
	n %= 16;
	write(1, &base[n], 1);
	return (i + 1);
}
