/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:32:01 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/12 16:54:31 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(char c, va_list params)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg (params, int));
	else if (c == 's')
		count += ft_putstr(va_arg (params, char *));
	else if (c == 'p')
		count += ft_putptr(va_arg (params, unsigned long long));
	else if (c == 'd')
		count += ft_putnbr(va_arg(params, int));
	else if (c == 'i')
		count += ft_putnbr(va_arg(params, int));
	else if (c == 'u')
		count += ft_putnbr(va_arg(params, unsigned int));
	else if (c == 'x' || c == 'X')
		count += ft_puthex(va_arg(params, unsigned int), c);
	else if (c == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
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
			count += ft_check(format[1], params);
			format++;
		}
		else
			count += ft_putchar(*format);
		format++;
	}
	va_end(params);
	return (count);
}
