/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:32:01 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/13 17:48:50 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printfd.h"

int	ft_checkd(char c, va_list params, int fd)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchard(va_arg (params, int), fd);
	else if (c == 's')
		count += ft_putstrd(va_arg (params, char *), fd);
	else if (c == 'p')
		count += ft_putptrd(va_arg (params, unsigned long long), fd);
	else if (c == 'd')
		count += ft_putnbrd(va_arg(params, int), fd);
	else if (c == 'i')
		count += ft_putnbrd(va_arg(params, int), fd);
	else if (c == 'u')
		count += ft_putnbrd(va_arg(params, unsigned int), fd);
	else if (c == 'x' || c == 'X')
		count += ft_puthexd(va_arg(params, unsigned int), c, fd);
	else if (c == '%')
		count += ft_putchard('%', fd);
	return (count);
}

int	ft_printfd(int fd, const char *format, ...)
{
	int		count;
	va_list	params;

	if (!format)
		return (-1);
	va_start(params, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			count += ft_checkd(format[1], params, fd);
			format++;
		}
		else
			count += ft_putchard(*format, fd);
		format++;
	}
	va_end(params);
	return (count);
}
