/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:14:47 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/13 17:51:18 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printfd.h"

int	ft_putchard(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

size_t	ft_putstrd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (s[i])
		i++;
	write(fd, s, i);
	return (i);
}

int	ft_putnbrd(long long n, int fd)
{
	int	i;

	i = 0;
	if (n == 0)
		return (write(fd, "0", 1));
	if (n < 0)
	{
		i += ft_putchard('-', fd);
		n = -n;
	}
	if (n >= 10)
		i += ft_putnbrd(n / 10, fd);
	i += ft_putchard((n % 10) + 48, fd);
	return (i);
}

int	ft_puthexd(long long n, char c, int fd)
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
		i += ft_puthexd(n / 16, c, fd);
	n %= 16;
	write(fd, &base[n], 1);
	return (i + 1);
}

int	ft_putptrd(unsigned long long n, int fd)
{
	char	*base;
	int		i;

	i = 0;
	base = "0123456789abcdef";
	if (n == 0)
		return (write(fd, "(nil)", 5));
	if (n >= 16)
		i += ft_putptrd(n / 16, fd);
	if (i == 0)
	{
		write(fd, "0x", 2);
		i += 2;
	}
	n %= 16;
	write(fd, &base[n], 1);
	return (i + 1);
}
