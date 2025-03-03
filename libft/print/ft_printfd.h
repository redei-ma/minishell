/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:07:01 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/13 17:50:01 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTFD_H
# define FT_PRINTFD_H

# include "libft.h"

int		ft_checkd(char c, va_list params, int fd);

int		ft_putchard(char c, int fd);
size_t	ft_putstrd(char *s, int fd);
int		ft_putnbrd(long long n, int fd);
int		ft_puthexd(long long n, char c, int fd);
int		ft_putptrd(unsigned long long n, int fd);

#endif
