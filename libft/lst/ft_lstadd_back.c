/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:07 by redei-ma          #+#    #+#             */
/*   Updated: 2025/01/28 15:02:48 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *niu)
{
	t_list	*last;

	if (!lst || !niu)
		return ;
	if (!*lst)
	{
		*lst = niu;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = niu;
}

/* int	main ()
{
	
} */